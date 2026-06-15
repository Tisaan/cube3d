/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_seed_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 19:23:22 by tseche            #+#    #+#             */
/*   Updated: 2026/06/09 15:04:07 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bonus.h"
#include <stdio.h>
#include <time.h>
#include <math.h>

bool	check_seed(long seed)
{
	if (seed == 0 || seed < 0)
		return (false);
	if (ft_count_digits(seed) != 12)
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

void	init_dir(t_map_simu *map)
{
	map->dir_x[0] = 1;
	map->dir_x[1] = -1;
	map->dir_x[2] = 1;
	map->dir_x[3] = 0;
	map->dir_x[4] = 0;
	map->dir_x[5] = -1;
	map->dir_x[6] = 1;
	map->dir_x[7] = -1;
	map->dir_y[0] = -1;
	map->dir_y[1] = 1;
	map->dir_y[2] = -1;
	map->dir_y[3] = 0;
	map->dir_y[4] = 0;
	map->dir_y[5] = 1;
	map->dir_y[6] = -1;
	map->dir_y[7] = 1;
}

t_map_simu	*seed_to_mapsimu(long int seed)
{
	t_map_simu	*map;

	map = ft_calloc(sizeof(t_map_simu), 1);
	if (!map)
		return (NULL);
	map->len = ft_count_digits(seed);
	map->ori_x = (seed / powl(10, 10));
	map->ori_y = ((int)(seed / powl(10, 8)) % 100);
	map->height = ((int)(seed / powl(10, 5)) % 1000) / 4;
	map->width = ((long)(seed / 100) % 1000) / 4;
	map->iter = seed % 100 * 100;
	map->door = ((float)(seed % 10) / 10);
	init_dir(map);
	return (map);
}
