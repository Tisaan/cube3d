/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 17:19:07 by tseche            #+#    #+#             */
/*   Updated: 2026/05/09 16:36:53 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus.h"

bool	door_placeable(t_map_simu *map, int x, int y)
{
	if (map->map[(map->height + x + 1) % map->height][y] == ' ' &&
		map->map[(map->height + x - 1) % map->height][y] == ' ' &&
		map->map[x][(map->width + y + 1) % map->width] == '1' &&
		map->map[x][(map->width + y - 1) % map->width] == '1')
		return (true);
	else if (map->map[(map->height + x + 1) % map->height][y] == '1' &&
		map->map[(map->height + x - 1) % map->height][y] == '1' &&
		map->map[x][(map->width + y + 1) % map->width] == ' ' &&
		map->map[x][(map->width + y - 1) % map->width] == ' ')
		return (true);
	return (false);
}

void	place_door(t_map_simu *map)
{
	int		x;
	int		y;
	float	ran;

	x = 0;
	while (map->map[x])
	{
		y = 0;
		while (map->map[x][y])
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
