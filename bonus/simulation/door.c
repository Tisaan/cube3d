/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 17:19:07 by tseche            #+#    #+#             */
/*   Updated: 2026/05/21 16:04:55 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus.h"

bool	door_placeable(t_map_simu *map, int x, int y)
{
	if (map->map[x + 1][y] &&
		map->map[x - 1][y] &&
		map->map[x][y + 1] &&
		map->map[x][y - 1])
	{
		if (map->map[x + 1][y] == '0' &&
			map->map[x - 1][y] == '0' &&
			map->map[x][y + 1] == '1' &&
			map->map[x][y - 1] == '1')
			return (true);
		else if (map->map[x + 1][y] == '1' &&
			map->map[x - 1][y] == '1' &&
			map->map[x][y + 1] == '0' &&
			map->map[x][y - 1] == '0')
			return (true);
	}
	return (false);
}

void	place_door(t_map_simu *map)
{
	int		x;
	int		y;
	float	ran;

	x = 1;
	while (x < map->height - 1)
	{
		y = 1;
		while (y < map->width - 1)
		{
			if (door_placeable(map, x, y))
			{
				ran = (float)rand() / (float)RAND_MAX;
				if (ran <= map->door)
					map->map[x][y] = 'D';
			}
			y++;
		}
		x++;
	}
}
