/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_seed.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 19:23:22 by tseche            #+#    #+#             */
/*   Updated: 2026/05/07 17:53:06 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus.h"
#include <time.h>
#include <math.h>


//cycle: 1 si len(seed) == 8, sinon 0
//seed: NULL si non provided par user
int	*get_range(int cycle, int *seed)
{
	int		range[2];

	range[0] = 2222222;
	range[1] = 6666666;
	if (cycle)
	{
		range[0] = 11111111;
		range[1] = 77777777;
	}
	if (seed)
	{
		if (*seed < range[0])
			*seed += range[0];
		else if (*seed > range[1])
			*seed -= range[1];
	}
	return (range);
}

int	gen_seed(int min, int max)
{
	int		range;
	static 	first = 1;
	int		limit;
	int		value;

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
	map->stof = seed / (powl(10, map->len - i++));
	map->ftof = (int)(seed / (powl(10, map->len - i++))) % 10;
	map->ftow = (int)(seed / (powl(10, map->len - i++))) % 10;
	if (map->len == 8)
		map->wtos = (int)(seed / (powl(10, map->len - i++))) % 10;
	map->iter = (seed % (int)powl(10, map->len - (i - 1)) / 100);
	i += 2;
	map->door = (float)(((int)(seed / (powl(10, map->len - i++)))) % 10) / 10;
	map->wall = (int)(seed / (powl(10, map->len - i++))) % 2;
	map->width = (seed % 1000);
	map->height = seed / powl(10, map->len - 3);
	map->min = 2;
	map->max = 6;
	if (map->len == 8)
		map->min = 1;
	if (map->len == 8)
		map->max = 7;
	return (map);
}

void debug_seed(t_map_simu *map)
{
    printf("len:%d\n", map->len);
    printf("stof:%d\n", map->stof);
    printf("ftof:%d\n", map->ftof);
    printf("ftow:%d\n", map->ftow);
    if (map->wtos)
        printf("wtos:%d\n", map->wtos);
    printf("door:%d\n", map->door);
    printf("wall:%d\n", (int)map->wall);
    printf("width:%d\n", map->width);
    printf("height:%d\n", map->height);
}


