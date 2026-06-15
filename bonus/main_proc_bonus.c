/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_proc_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 15:24:28 by von               #+#    #+#             */
/*   Updated: 2026/06/15 16:46:21 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/bonus.h"

void	link_zero(t_map_simu *map)
{
	int	i;
	int	j;

	i = 2;
	while (i < map->height - 2)
	{
		j = 2;
		while (j < map->width - 2)
		{
			if (map->map[i][j] == '0')
				place_zero(map, i, j);
			j++;
		}
		i++;
	}
}

void	place_struct(t_map_simu *map)
{
	int	i;
	int	j;
	int	index;
	int	len;

	i = 0;
	len = ft_strlen(map->seed);
	index = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->map[i][j] == '0' && nb_zero_neighbour(map, i, j) >= 6
				&& map->seed[(len + index++) % len] == '1')
				map->map[i][j] = '1';
			j++;
		}
		i++;
	}
}

void	gen_map_algo(t_map_simu *map, t_point *pos)
{
	int			i;
	t_pointlist	*list;

	i = 0;
	list = initpoints(map->iter * 2);
	if (!list)
		return ;
	while (i < map->iter)
	{
		if (place_gen_algo(pos, map, list, i++))
			return ;
	}
	free_pointlist(list);
}

bool	generate_map(t_data *data, t_map_simu *map, long int seed)
{
	const t_point	val = {.x = map->ori_x,
		.y = map->ori_y};

	map->seed = ft_calloc(sizeof(char), 65);
	if (!map->seed)
	{
		free_t_map_simu(map);
		throw_error_bonus(ERR_MALLOC_BNS);
		return (false);
	}
	generate_map_process(map, seed, val);
	free(map->seed);
	data->seed = str_seed(seed);
	if (!data->seed || map_empty(map))
	{
		if (data->seed)
			free(data->seed);
		throw_error_bonus(MAP_EMPTY_GEN);
		free_t_map_simu(map);
		return (false);
	}
	return (true);
}

t_data	*main_proc(long int seed)
{
	t_data		*data;
	t_map_simu	*map;

	data = ft_calloc(sizeof(t_data), 1);
	if (!data)
	{
		throw_error(ERROR_MALLOC);
		return (NULL);
	}
	map = init_map(data, seed);
	if (!map)
		return (NULL);
	map->spawn = (t_int3){.zero = -1, .one = 0,
		.two = "NSEW"[add_digit_number(seed) % 4]};
	if (place_spawn(map) == 0)
	{
		throw_error_bonus(MAP_NO_SPAWN);
		free_t_map_simu(map);
		free(data);
		return (NULL);
	}
	data->map = convert_map_simu_to_map(map);
	return (data);
}
