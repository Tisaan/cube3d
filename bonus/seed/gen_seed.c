/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_seed.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 19:23:22 by tseche            #+#    #+#             */
/*   Updated: 2026/05/21 18:12:36 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus.h"
#include <stdio.h>
#include <time.h>
#include <math.h>

bool	check_seed(long seed)
{
	if (seed == 0)
		return (false);
	if ((seed / powl(10, 10)) >= ((int)(seed / powl(10, 5)) % 1000))
		return (false);
	else if (((int)(seed / powl(10, 8)) % 100) >= ((long)(seed / 100) % 1000))
		return (false);
	return (true);
}

long int	gen_seed(void)
{
	const long long	min = 100000000000LL;
	const long long	max = 999999999999LL;
	long long		value;

	srandom(time(NULL));
	value = 0;
	while (!check_seed(value))
	{
		value = ((long long)random() << 32) | random();
		value = min + (value % (max - min + 1));
	}
	return (value);
}

t_map_simu	*seed_to_mapsimu(long int seed)
{
	t_map_simu	*map;

	map = calloc(sizeof(t_map_simu), 1);
	if (!map)
		return (NULL);
	map->len = ft_count_digits(seed);
	map->ori_x = (seed / powl(10, 10));
	map->ori_y = ((int)(seed / powl(10, 8)) % 100);
	map->height = ((int)(seed / powl(10, 5)) % 1000) / 4;
	map->width = ((long)(seed / 100) % 1000) / 4;
	map->iter = seed % 100 * 100;
	map->door = ((float)(seed % 10) / 10);
	return (map);
}

void	debug_seed(t_map_simu *map, long int seed, bool print)
{
	int	i;

	if (print)
	{
		i = 0;
		printf("map:\n");
		while (i <= map->height)
			printf("%s\n", map->map[i++]);
		printf("end map\n");
		return;
	}
	printf("seed:%ld\n", seed);
	printf("len:%d\n", map->len);
	printf("ori_x:%d\n", map->ori_x);
	printf("ori_y:%d\n", map->ori_y);
	printf("height:%d\n", map->height);
	printf("width:%d\n", map->width);
	printf("iter:%d\n", map->iter);
	printf("door:%f\n", map->door);
}
