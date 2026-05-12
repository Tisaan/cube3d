/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 15:15:18 by tseche            #+#    #+#             */
/*   Updated: 2026/05/11 16:10:20 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus.h"

bool	between(int a, int b, int c)
{
	return ((c >= a && c <= b) || (c >= b && c <= a));
}

bool	had_space_neighbour(t_map_simu *map, int x, size_t y)
{
	const int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    const int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};
	
    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        // Check if the neighbor is within grid boundaries
        if (nx >= 0 && nx < map->width && ny >= 0 && ny < map->height)
		{
			// printf("x:%d, y:%d, height:%d, width:%d\n", nx, ny, map->height, map->width);
			if (map->map[nx][ny] == ' ')
            	return (true);
        }
	}
	return (false);
}


