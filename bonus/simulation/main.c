/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 17:42:13 by tseche            #+#    #+#             */
/*   Updated: 2026/05/22 16:56:57 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus.h"

void	l_shape(t_int2 pos, int i, t_map_simu *map)
{
	const int	table[3] = {-1, 0, 1};
	int			num;

	num = table[i % 3];
	if (i % 4 == 0)
	{
		pos = (t_int2){.zero = pos.zero + 2, .one = pos.one + num};
	}
	else if (i % 4 == 1)
	{
		pos = (t_int2){.zero = pos.zero - 2, .one = pos.one + num};
	}
	else if (i % 4 == 2)
	{
		pos = (t_int2){.zero = pos.zero + num, .one = pos.one + 2};
	}
	else
	{
		pos = (t_int2){.zero = pos.zero + num, .one = pos.one - 2};
	}
	pos.zero += ((int [8])dir_x)[(map->iter - i + (i % 2 == 0)) % 8];
	pos.one += ((int [8])dir_y)[(i - map->iter + (i % 2 == 1)) % 8];
}

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
			{
				if (map->map[i - 2][j] == '0')
					map->map[i - 1][j] = '0';
				if (map->map[i + 2][j] == '0')
					map->map[i + 1][j] = '0';
				if (map->map[i][j - 2] == '0')
					map->map[i][j - 1] = '0';
				if (map->map[i][j + 2] == '0')
					map->map[i][j + 1] = '0';
			}
			j++;
		}
		i++;
	}
}

void	gen_map_algo(t_map_simu *map, char *seed, t_int2 pos, int total)
{
	int			i;
	size_t		index;

	i = 0;
	index = 0;
	while (i < map->iter)
	{
		if ((pos.zero < map->height && pos.zero >= 0)
			&& (pos.one < map->width && pos.one >= 0))
		{
			if (map->map[pos.zero][pos.one] != '0')
			{
				pos.zero += ((int [8])dir_x)[(map->iter - i) % 8];
				pos.one += ((int [8])dir_y)[(i - map->iter) % 8];
				if (++total == map->iter)
					return ;
				continue ;
			}
			map->map[pos.zero][pos.one] = seed[(ft_strlen(seed) + index++)
				% ft_strlen(seed)];
		}
		else
			pos = (t_int2){.zero = map->ori_x, .one = map->ori_y};
		l_shape(pos, i++, map);
	}
}

bool	generate_map(t_map_simu *map, long int seed)
{
	char	*str_seed;

	str_seed = ft_calloc(sizeof(char), 65);
	if (!str_seed)
	{
		free_t_map_simu(map);
		throw_error_bonus(ERR_MALLOC_BNS);
		return (false);
	}
	int_to_bin_str(seed, (char *)str_seed);
	gen_map_algo(map, str_seed, (t_int2){.zero = map->ori_x,
		.one = map->ori_y}, 0);
	link_zero(map);
	apply_wall(map);
	place_door(map);
	free(str_seed);
	if (map_empty(map))
	{
		throw_error_bonus(MAP_EMPTY_GEN);
		free_t_map_simu(map);
		return (false);
	}
	return (true);
}

int	main(void)
{
	t_map_simu		*map;
	const long int	seed = gen_seed();
	int				i;

	map = seed_to_mapsimu(seed);
	map->map = ft_calloc(map->height + 1, sizeof(int *));
	i = 0;
	while (i <= map->height)
	{
		map->map[i] = ft_calloc(sizeof(int), map->width + 1);
		ft_memset(map->map[i], ' ', map->width);
		i++;
	}
	if (!generate_map(map, seed))
		return (1);
	map->spawn = (t_int3){.zero = -1, .one = 0,
		.two = "NSEW"[add_digit_number(seed) % 4]};
	if (place_spawn(map) == 0)
	{
		throw_error_bonus(MAP_NO_SPAWN);
		free_t_map_simu(map);
		return (1);
	}
	debug_seed(map, seed, 1);
	debug_seed(map, seed, 0);
	free_t_map_simu(map);
}
