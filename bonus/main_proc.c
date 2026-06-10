/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_proc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 15:24:28 by von               #+#    #+#             */
/*   Updated: 2026/06/10 12:34:38 by pcaplat          ###   ########.fr       */
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

void	generate_map_process(t_map_simu *map, long int seed, const t_point val)
{
	int_to_bin_str(seed, map->seed);
	gen_map_algo(map, (t_point *)&val);
	link_zero(map);
	place_struct(map);
	apply_wall(map);
	place_door(map);
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
	data->seed = map->seed;
	for (int i = 0; data->seed[i]; i++)
		write(1, &data->seed[i], 1);
	if (map_empty(map))
	{
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
