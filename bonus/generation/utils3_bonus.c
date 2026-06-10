/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 17:46:35 by tseche            #+#    #+#             */
/*   Updated: 2026/06/10 10:48:31 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bonus.h"

bool	place_outbound(t_point *pos, t_map_simu *map, t_pointlist *list, int i)
{
	pos->x = map->ori_x;
	pos->y = map->ori_y;
	if (!addpointfree(list, *pos, map))
		return (true);
	l_shape(pos, i, map);
	if (!addpointfree(list, *pos, map))
		return (true);
	return (false);
}

bool	place_gen_algo(
	t_point *pos,
	t_map_simu *map,
	t_pointlist *list,
	int i
){
	static int	index = 0;
	static int	total = 0;

	if ((pos->x < map->height && pos->x >= 0)
		&& (pos->y < map->width && pos->y >= 0))
	{
		if (map->map[pos->x][pos->y] == '0')
		{
			if (!addpointfree(list, *pos, map))
				return (true);
			pos->x += map->dir_x[abs(map->iter - (i + map->ori_y)) % 8];
			pos->y += map->dir_y[abs(map->iter - (i + map->ori_y)) % 8];
			if (++total == map->iter)
			{
				free_pointlist(list);
				return (true);
			}
			if (!addpointfree(list, *pos, map))
				return (true);
			return (false);
		}
		return (place_bound(map, pos, &index, list));
	}
	else
		return (place_outbound(pos, map, list, i));
}

void	l_shape(t_point *pos, int i, t_map_simu *map)
{
	int			num;

	num = (int [3]){-1, 0, 1}[(map->ori_x + map->ori_y + i) % 3];
	if (i % 4 == 0)
		(*pos).x = (*pos).x + 2;
	if (i % 4 == 0)
		(*pos).y = (*pos).y + num;
	else if (i % 4 == 1)
		(*pos).x = (*pos).x - 2;
	else if (i % 4 == 1)
		(*pos).y = (*pos).y + num;
	else if (i % 4 == 2)
		(*pos).x = (*pos).x + num;
	else if (i % 4 == 2)
		(*pos).y = (*pos).y + 2;
	else
	{
		(*pos).x = (*pos).x + num;
		(*pos).y = (*pos).y - 2;
	}
	(*pos).x += map->dir_x[(map->iter - i
			+ ((map->ori_x + i) % 2 == 0)) % 8];
	(*pos).y += map->dir_y[(map->iter - i
			+ ((map->ori_y + i) % 2 == 1)) % 8];
}

void	place_point_loop(t_map_simu *map, t_pointlist *p)
{
	int		iter;
	t_point	prev;
	t_point	pos;

	if (p->len == 0 || p->len == 1)
		return ;
	iter = 1;
	while (iter < p->len)
	{
		prev = p->point[iter - 1];
		pos = p->point[iter];
		place_point(map, prev, pos);
		iter++;
	}
}

t_map_simu	*init_map(t_data *data, long int seed)
{
	t_map_simu	*map;
	int			i;

	map = seed_to_mapsimu(seed);
	map->map = ft_calloc(map->height + 1, sizeof(char *));
	i = 0;
	while (i < map->height)
	{
		map->map[i] = ft_calloc(sizeof(char), map->width + 1);
		ft_memset(map->map[i], ' ', map->width);
		i++;
	}
	if (!generate_map(data, map, seed))
	{
		free(data);
		return (NULL);
	}
	if (!map->map)
	{
		throw_error_bonus(ERR_MALLOC_BNS);
		free_t_map_simu(map);
		free(data);
		return (NULL);
	}
	return (map);
}
