/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 12:21:06 by tseche            #+#    #+#             */
/*   Updated: 2026/05/15 18:16:24 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus.h"
#include <stdio.h>
#include <unistd.h>

void	wall(t_map_simu *map, int x, int y)
{
	int	i;
	int	j;
	// if (map->wall == 0 && had_space_neighbour(map, x, y))
	// 	map->map[x][y] = '1'; 
	if (had_space_neighbour(map, x, y))
	{
		i = -1;
		while (i <= 1)
		{
			j = -1;
			while (j <= 1)
			{
				if (map->map[(map->height + x) % map->height][(map->width + y) % map->width] == '0')
					map->map[(map->height + x + i) % map->height][(map->width + y + j) % map->width] = '1';
				j++;
			}
			i++;
		}
	}
	
}

void	apply_wall(t_map_simu *map)
{
	int	x;
	int	y;
	int i;

	x = 1;
	while (x <= map->height)
	{
		y = 1;
		while (y <= map->width)
		{
			if (map->map[x][y] == '0')
				wall(map, x, y);
			y++;
		}
		x++;
	}
	i = 0;
	while (i <= map->width)
	{
		if (map->map[0][i] == '0')
			map->map[0][i] = '1';
		if (map->map[map->height][i] == '0')
			map->map[map->height][i] = '1';
		i++;
	}
	i = 0;
	while (i <= map->height)
	{
		if (map->map[i][0] == '0')
			map->map[i][0] = '1';
		if (map->map[i][map->width] == '0')
			map->map[i][map->width] = '1';
		i++;
	}
}


