/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 12:21:06 by tseche            #+#    #+#             */
/*   Updated: 2026/05/22 14:26:59 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus.h"

void	wall(t_map_simu *map, int x, int y)
{
	int	i;
	int	j;

	if (had_space_neighbour(map, x, y))
	{
		i = -1;
		while (i <= 1)
		{
			j = -1;
			while (j <= 1)
			{
				if (map->map[x + i][y + j] == ' ')
					map->map[x + i][y + j] = '1';
				j++;
			}
			i++;
		}
	}
}

void	wall_border(t_map_simu *map)
{
	int	x;

	x = 0;
	while (x <= map->width)
	{
		if (map->map[0][x] == '0')
			map->map[0][x] = '1';
		if (map->map[map->height][x] == '0')
			map->map[map->height][x] = '1';
		x++;
	}
	x = 0;
	while (x <= map->height)
	{
		if (map->map[x][0] == '0')
			map->map[x][0] = '1';
		if (map->map[x][map->width] == '0')
			map->map[x][map->width] = '1';
		x++;
	}
}

void	apply_wall(t_map_simu *map)
{
	int	x;
	int	y;

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
	wall_border(map);
}
