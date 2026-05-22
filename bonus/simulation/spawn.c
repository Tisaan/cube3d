/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: von <von@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 01:19:29 by von               #+#    #+#             */
/*   Updated: 2026/05/22 02:09:53 by von              ###   ########.fr       */
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
	nmap->start[0] = map->spawn[0];
	nmap->start[1] = map->spawn[1];
	nmap->start[2] = map->spawn[2];
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
	map->spawn[0] = -1;
	map->spawn[2] = "NSEW"[add_digit_number(seed) % 4];
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->map[i][j] == '0' && chebyshev(map, i, j) < min)
			{
				min = chebyshev(map, i, j);
				map->spawn[0] = i;
				map->spawn[1] = j;
			}
			j++;
		}
		i++;
	}
	if (map->spawn[0] == -1)
		return (0);
	map->map[map->spawn[0]][map->spawn[1]] = map->spawn[2];
	return (1);
}
