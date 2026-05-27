/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   method.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: von <von@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 15:14:45 by von               #+#    #+#             */
/*   Updated: 2026/05/27 16:20:51 by von              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus.h"

t_path* create_t_path(int capacity)
{
    t_path *p = malloc(sizeof(t_path));
    p->points = malloc(capacity * sizeof(t_point));
    p->count = 0;
    p->capacity = capacity;
    return p;
}

void add_to_path(t_path *p, t_point point) {
    if (p->count < p->capacity)
	{
        p->points[p->count++] = point;
    }
}

void reverse_path(t_path *p) {
	t_point	temp;
	int		i;

	i = 0;
    while (i < p->count / 2)
	{
    	temp = p->points[i];
        p->points[i] = p->points[p->count - 1 - i];
        p->points[p->count - 1 - i] = temp;
		i++;
    }
}

t_path* find_shortest_path(char **grid, int rows, int cols, t_point start, t_point end)
{
    if (start.row < 0 || start.row >= rows || start.col < 0 || start.col >= cols ||
        end.row < 0 || end.row >= rows || end.col < 0 || end.col >= cols) {
        return NULL;
    }

    // Allocate visited and parent matrices
    bool **visited = malloc(rows * sizeof(bool *));
    t_point **parent = malloc(rows * sizeof(t_point *));
    for (int i = 0; i < rows; i++) {
        visited[i] = calloc(cols, sizeof(bool));
        parent[i] = malloc(cols * sizeof(t_point));
        for (int j = 0; j < cols; j++) {
            parent[i][j] = (t_point){-1, -1}; // Sentinel value
        }
    }

    // 4-directional movement: up, down, left, right
    int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    t_queue *q = create_queue(rows * cols);
    enqueue(q, start);
    visited[start.row][start.col] = true;
    parent[start.row][start.col] = (t_point){-1, -1}; // Mark start

    bool found = false;

    while (!is_empty(q)) {
        t_point current = dequeue(q);

        if (current.row == end.row && current.col == end.col) {
            found = true;
            break;
        }

        for (int i = 0; i < 4; i++) {
            int ni = current.row + dirs[i][0];
            int nj = current.col + dirs[i][1];

            if (ni >= 0 && ni < rows && nj >= 0 && nj < cols && !visited[ni][nj]) {
                visited[ni][nj] = true;
                parent[ni][nj] = current;
                enqueue(q, (t_point){ni, nj});
            }
        }
    }

    // Reconstruct t_path if found
    if (!found) {
        for (int i = 0; i < rows; i++) {
            free(visited[i]);
            free(parent[i]);
        }
        free(visited);
        free(parent);
        free_queue(q);
        return NULL;
    }

    t_path *t_path = create_t_path(rows * cols);
    t_point current = end;
    while (current.row != -1 && current.col != -1) {
        add_to_path(t_path, current);
        current = parent[current.row][current.col];
    }
    reverse_path(t_path);

    // Cleanup
    for (int i = 0; i < rows; i++) {
        free(visited[i]);
        free(parent[i]);
    }
    free(visited);
    free(parent);
    free_queue(q);

    return t_path;
}