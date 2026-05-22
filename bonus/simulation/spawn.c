/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 01:19:29 by von               #+#    #+#             */
/*   Updated: 2026/05/22 14:41:01 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus.h"

t_map	*convert_map_simu_to_map(t_map_simu *map)
{
	t_map	*nmap;

	nmap = ft_calloc(sizeof(t_map), 1);
	if (!nmap)
		return (NULL);
	nmap->grid = map->map;
	nmap->height = map->height;
	nmap->width = map->height;
	nmap->start = ft_calloc(sizeof(int), 3);
	if (!nmap->start)
		return (NULL);
	nmap->start[0] = map->spawn.zero;
	nmap->start[1] = map->spawn.one;
	nmap->start[2] = map->spawn.two;
	return (nmap);
}

int	chebyshev(t_map_simu *map, int x, int y)
{
	if (abs(map->ori_x - x) > abs(map->ori_y - y))
		return (abs(map->ori_x - x));
	return (abs(map->ori_y - y));
}

int	place_spawn(t_map_simu *map, long int seed)
{
	int	min;
	int	i;
	int	j;

	min = map->height;
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->map[i][j] == '0' && chebyshev(map, i, j) < min)
			{
				min = chebyshev(map, i, j);
				map->spawn = (t_int3){.zero = i,
					.one = j, .two = map->spawn.two};
			}
			j++;
		}
		i++;
	}
	if (map->spawn.zero == -1)
		return (0);
	map->map[map->spawn.zero][map->spawn.one] = map->spawn.two;
	return (1);
}
