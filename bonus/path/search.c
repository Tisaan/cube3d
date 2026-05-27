/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: von <von@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 16:17:55 by von               #+#    #+#             */
/*   Updated: 2026/05/27 16:20:02 by von              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus.h"

void* forward_bfs(void *arg) {
    BFSData *data = (BFSData *)arg;
    int dirs[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};

    while (1) {
        pthread_mutex_lock(&data->found_mutex);
        if (data->found) {
            pthread_mutex_unlock(&data->found_mutex);
            pthread_cond_broadcast(&data->found_cond);
            break;
        }
        pthread_mutex_unlock(&data->found_mutex);

        if (is_empty(data->forward_queue)) break;

        t_point current = dequeue(data->forward_queue);

        // Check if backward BFS visited this node
        if (data->backward_visited[current.row][current.col]) {
            pthread_mutex_lock(&data->found_mutex);
            data->found = true;
            data->meeting_point = current;
            pthread_cond_broadcast(&data->found_cond);
            pthread_mutex_unlock(&data->found_mutex);
            break;
        }

        // Explore neighbors
        for (int i = 0; i < 4; i++) {
            int ni = current.row + dirs[i][0];
            int nj = current.col + dirs[i][1];
            if (ni >= 0 && ni < data->rows && nj >= 0 && nj < data->cols && !data->forward_visited[ni][nj]) {
                data->forward_visited[ni][nj] = true;
                data->forward_parent[ni][nj] = current;
                enqueue(data->forward_queue, (t_point){ni, nj});
            }
        }
    }
    return NULL;
}

void* backward_bfs(void *arg) {
    BFSData *data = (BFSData *)arg;
    int dirs[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};

    while (1) {
        pthread_mutex_lock(&data->found_mutex);
        if (data->found) {
            pthread_mutex_unlock(&data->found_mutex);
            pthread_cond_broadcast(&data->found_cond);
            break;
        }
        pthread_mutex_unlock(&data->found_mutex);

        if (is_empty(data->backward_queue)) break;

        t_point current = dequeue(data->backward_queue);

        // Check if forward BFS visited this node
        if (data->forward_visited[current.row][current.col]) {
            pthread_mutex_lock(&data->found_mutex);
            data->found = true;
            data->meeting_point = current;
            pthread_cond_broadcast(&data->found_cond);
            pthread_mutex_unlock(&data->found_mutex);
            break;
        }

        // Explore neighbors
        for (int i = 0; i < 4; i++) {
            int ni = current.row + dirs[i][0];
            int nj = current.col + dirs[i][1];
            if (ni >= 0 && ni < data->rows && nj >= 0 && nj < data->cols && !data->backward_visited[ni][nj]) {
                data->backward_visited[ni][nj] = true;
                data->backward_parent[ni][nj] = current;
                enqueue(data->backward_queue, (t_point){ni, nj});
            }
        }
    }
    return NULL;
}

t_path* find_shortest_path_bidirectional_parallel(char **grid, int rows, int cols, t_point start, t_point end) {
    if (start.row < 0 || start.row >= rows || start.col < 0 || start.col >= cols ||
        end.row < 0 || end.row >= rows || end.col < 0 || end.col >= cols) {
        return NULL;
    }

    BFSData data;
    data.grid = grid;
    data.rows = rows;
    data.cols = cols;
    data.start = start;
    data.end = end;
    data.found = false;
    pthread_mutex_init(&data.found_mutex, NULL);
    pthread_cond_init(&data.found_cond, NULL);

    // Initialize queues
    data.forward_queue = create_queue(rows * cols);
    data.backward_queue = create_queue(rows * cols);

    // Allocate visited/parent matrices
    data.forward_visited = malloc(rows * sizeof(bool *));
    data.backward_visited = malloc(rows * sizeof(bool *));
    data.forward_parent = malloc(rows * sizeof(t_point *));
    data.backward_parent = malloc(rows * sizeof(t_point *));
    for (int i = 0; i < rows; i++) {
        data.forward_visited[i] = calloc(cols, sizeof(bool));
        data.backward_visited[i] = calloc(cols, sizeof(bool));
        data.forward_parent[i] = malloc(cols * sizeof(t_point));
        data.backward_parent[i] = malloc(cols * sizeof(t_point));
        for (int j = 0; j < cols; j++) {
            data.forward_parent[i][j] = (t_point){-1, -1};
            data.backward_parent[i][j] = (t_point){-1, -1};
        }
    }

    // Initialize BFS
    enqueue(data.forward_queue, start);
    data.forward_visited[start.row][start.col] = true;
    enqueue(data.backward_queue, end);
    data.backward_visited[end.row][end.col] = true;

    // Create threads
    pthread_t forward_thread, backward_thread;
    pthread_create(&forward_thread, NULL, forward_bfs, &data);
    pthread_create(&backward_thread, NULL, backward_bfs, &data);

    // Wait for threads
    pthread_join(forward_thread, NULL);
    pthread_join(backward_thread, NULL);

    // Reconstruct path if found
    if (!data.found) {
        for (int i = 0; i < rows; i++) {
            free(data.forward_visited[i]);
            free(data.backward_visited[i]);
            free(data.forward_parent[i]);
            free(data.backward_parent[i]);
        }
        free(data.forward_visited);
        free(data.backward_visited);
        free(data.forward_parent);
        free(data.backward_parent);
        free_queue(data.forward_queue);
        free_queue(data.backward_queue);
        pthread_mutex_destroy(&data.found_mutex);
        pthread_cond_destroy(&data.found_cond);
        return NULL;
    }

    // Combine forward and backward paths
    t_path *path = create_path(rows * cols * 2);

    // Forward: start -> meeting_point
    t_point current = data.meeting_point;
    while (current.row != -1 && current.col != -1) {
        add_to_path(path, current);
        current = data.forward_parent[current.row][current.col];
    }
    reverse_path(path);

    // Backward: meeting_point -> end (excluding meeting_point)
    current = data.backward_parent[data.meeting_point.row][data.meeting_point.col];
    while (current.row != -1 && current.col != -1) {
        add_to_path(path, current);
        current = data.backward_parent[current.row][current.col];
    }

    // Cleanup
    for (int i = 0; i < rows; i++) {
        free(data.forward_visited[i]);
        free(data.backward_visited[i]);
        free(data.forward_parent[i]);
        free(data.backward_parent[i]);
    }
    free(data.forward_visited);
    free(data.backward_visited);
    free(data.forward_parent);
    free(data.backward_parent);
    free_queue(data.forward_queue);
    free_queue(data.backward_queue);
    pthread_mutex_destroy(&data.found_mutex);
    pthread_cond_destroy(&data.found_cond);

    return path;
}