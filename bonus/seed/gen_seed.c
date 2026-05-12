/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_seed.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 19:23:22 by tseche            #+#    #+#             */
/*   Updated: 2026/05/12 14:46:43 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus.h"
#include <time.h>
#include <math.h>



//seed: NULL si non provided par user
void	get_range(int *range, int *seed)
{
	range[0] = 2222222;
	range[1] = 6666666;
	if (seed)
	{
		if (*seed < range[0])
			*seed += range[0];
		else if (*seed > range[1])
			*seed -= range[1];
	}
}

int	gen_seed(int min, int max)
{
	int			range;
	static int 	first = 1;
	int			limit;
	int			value;

	if (first)
	{
		srand(time(NULL));
		first = 0;
	}
	range = max - min + 1;
	limit = RAND_MAX - (RAND_MAX % range);
	value = rand();
	while (value >= limit)
		value = rand();
	return (min + (value % range));
}

t_map_simu	*seed_to_mapsimu(int seed)
{
	t_map_simu	*map;
	int			i;

	map = ft_calloc(sizeof(t_map_simu), 1);
	if (!map)
		return (NULL);
	map->len = ft_count_digits(seed);
	i = 1;
	map->space = seed / (powl(10, map->len - i++));
	map->floor = (int)(seed / (powl(10, map->len - i++))) % 10;
	map->iter = (seed % (int)powl(10, map->len - (i - 1)) / 1000);
	i += 2;
	map->door = (float)(((int)(seed / (powl(10, map->len - i++)))) % 10) / 10;
	map->wall = (int)(seed / (powl(10, map->len - i++))) % 2;
	map->width = (seed % 1000) / 4;
	map->height = seed / powl(10, map->len - 3) / 4;
	return (map);
}

void debug_seed(t_map_simu *map)
{
	printf("iter:%d\n", map->iter);
    printf("len:%d\n", map->len);
    printf("space:%d\n", map->space);
    printf("floor:%d\n", map->floor);
    printf("door:%f\n", map->door);
    printf("wall:%d\n", (int)map->wall);
    printf("width:%d\n", map->width);
    printf("height:%d\n", map->height);
}


