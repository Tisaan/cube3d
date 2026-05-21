/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 17:31:20 by tseche            #+#    #+#             */
/*   Updated: 2026/05/21 18:16:23 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../../includes/bonus.h"

// Deep copy a group
t_group_gen copy_group(const t_group_gen *src) {
    t_group_gen dest = {NULL, 0};
    if (src->count > 0) {
        dest.coords = malloc(src->count * sizeof(t_coord));
        memcpy(dest.coords, src->coords, src->count * sizeof(t_coord));
        dest.count = src->count;
    }
    return dest;
}

// Free a group
void free_group(t_group_gen *g) {
    free(g->coords);
    g->coords = NULL;
    g->count = 0;
}

// DFS to collect '0' coordinates
void dfs_collect_zero(char **grid, bool **visited, int i, int j,
                      int rows, const int *cols, t_coord *coords, int *count) {
    if (i < 0 || i >= rows || j < 0 || j >= cols[i] || visited[i][j] || grid[i][j] != '0')
        return;
    visited[i][j] = true;
    coords[*count].row = i;
    coords[*count].col = j;
    (*count)++;
    // Explore von Neumann neighbors (up, down, left, right)
    dfs_collect_zero(grid, visited, i+1, j, rows, cols, coords, count);
    dfs_collect_zero(grid, visited, i-1, j, rows, cols, coords, count);
    dfs_collect_zero(grid, visited, i, j+1, rows, cols, coords, count);
    dfs_collect_zero(grid, visited, i, j-1, rows, cols, coords, count);
}



t_two_group find_biggest_groups(t_map_simu *map, int num_rows)
{
    t_two_group top = {{NULL, 0}, {NULL, 0}};
    if (num_rows == 0) return top;

    bool **visited = malloc(num_rows * sizeof(bool *));
    int *cols = malloc(num_rows * sizeof(int));
    int total_size = 0;
    for (int i = 0; i < num_rows; i++) {
        cols[i] = map->width;
        visited[i] = calloc(cols[i], sizeof(bool));
        total_size += cols[i];
    }

    t_coord *current_coords = malloc(total_size * sizeof(t_coord));

    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < cols[i]; j++) {
            // Only start DFS for '0'
            if (!visited[i][j] && map->map[i][j] == '0') {
                int current_count = 0;
                dfs_collect_zero(map->map, visited, i, j, num_rows, cols, current_coords, &current_count);

                t_group_gen current_group = {malloc(current_count * sizeof(t_coord)), current_count};
                memcpy(current_group.coords, current_coords, current_count * sizeof(t_coord));

                // Update top 2
                if (current_count > top.first.count) {
                    free_group(&top.second);
                    top.second = copy_group(&top.first);
                    free_group(&top.first);
                    top.first = current_group;
                } else if (current_count > top.second.count) {
                    free_group(&top.second);
                    top.second = current_group;
                } else {
                    free_group(&current_group);
                }
            }
        }
    }

    free(current_coords);
    for (int i = 0; i < num_rows; i++) free(visited[i]);
    free(visited);
    free(cols);

    return top;
}
