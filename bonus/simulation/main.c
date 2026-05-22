/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 17:42:13 by tseche            #+#    #+#             */
/*   Updated: 2026/05/22 15:25:44 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus.h"

void	int_to_bin_str(unsigned long num, char *dest)
{
	unsigned long	mask;
	int				index;

	if (num == 0)
	{
		ft_strcpy(dest, "0", 1);
		return ;
	}
	mask = 1UL << (sizeof(unsigned long) * 8 - 1);
	index = 0;
	while ((num & mask) == 0)
		mask >>= 1;
	while (mask != 0)
	{
		if (num & mask)
			dest[index++] = '1';
		else
			dest[index++] = '0';
		mask >>= 1;
	}
	dest[index] = '\0';
}

void	l_shape(int *pos, int i)
{
	const int	table[3] = {-1, 0, 1};
	int			num;

	num = table[i % 3];
	if (i % 4 == 0)
	{
		pos[0] = pos[0] + 2;
		pos[1] = pos[1] + num;
	}
	else if (i % 4 == 1)
	{
		pos[0] = pos[0] - 2;
		pos[1] = pos[1] + num;
	}
	else if (i % 4 == 2)
	{
		pos[0] = pos[0] + num;
		pos[1] = pos[1] + 2;
	}
	else
	{
		pos[0] = pos[0] + num;
		pos[1] = pos[1] - 2;
	}
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

void	gen_map_algo(t_map_simu *map, char *seed)
{
	int			pos[2];
	const int	dir_x[8] = {1, -1, 1, 0, 0, -1, 1, -1};
	const int	dir_y[8] = {-1, 1, -1, 0, 0, 1, -1, 1};
	int			i;
	int			total;
	size_t		index;

	i = 0;
	total = 0;
	pos[0] = map->ori_x;
	pos[1] = map->ori_y;
	index = 0;
	while (i < map->iter)
	{
		if (index >= ft_strlen(seed))
			index = 0;
		if ((pos[0] < map->height && pos[0] >= 0)
			&& (pos[1] < map->width && pos[1] >= 0))
		{
			if (map->map[pos[0]][pos[1]] == '0')
			{
				pos[0] = pos[0] + dir_x[(map->iter - i + total) % 8];
				pos[1] = pos[1] + dir_y[(i - map->iter) % 8];
				total++;
				if (total == map->iter)
					break ;
				continue ;
			}
			map->map[pos[0]][pos[1]] = seed[index++];
		}
		else
		{
			pos[0] = map->ori_x;
			pos[1] = map->ori_y;
		}
		l_shape(pos, i);
		pos[0] = pos[0] + dir_x[(map->iter - i + (i % 2 == 0)) % 8];
		pos[1] = pos[1] + dir_y[(i - map->iter + (i % 2 == 1)) % 8];
		i++;
	}
}

bool	generate_map(t_map_simu *map, long int seed)
{
	char	*str_seed;


	str_seed = ft_calloc(sizeof(char), 65);
	if (!str_seed)
		return (false);
	int_to_bin_str(seed, (char *)str_seed);
	gen_map_algo(map, str_seed);
	link_zero(map);
	apply_wall(map);
	place_door(map);
	free(str_seed);
	return (true);
}

int	main(void)
{
	const long int	seed = gen_seed();
 	t_map_simu		*map;

	map = seed_to_mapsimu(seed);
	map->map = ft_calloc(map->height + 1, sizeof(int *));
	for (int i = 0; i <= map->height; i++)
	{
		map->map[i] = ft_calloc(sizeof(int), map->width + 1);
		ft_memset(map->map[i], ' ', map->width);
	}
	if (!generate_map(map, seed))
	{
		free_t_map_simu(map);
		throw_error_bonus(ERROR_MALLOC);
		return (1);
	}
	if (map_empty(map))
	{
		debug_seed(map, seed, 0);
		throw_error_bonus(MAP_EMPTY_GEN);
		free_t_map_simu(map);
		return (1);
	}
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