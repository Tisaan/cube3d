/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_proc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/30 15:24:28 by von               #+#    #+#             */
/*   Updated: 2026/06/02 16:41:34 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/bonus.h"

void	l_shape(t_point *pos, int i, t_map_simu *map)
{
	int			num;

	num = (int [3]){-1, 0, 1}[(map->ori_x + map->ori_y + i) % 3];
	if (i % 4 == 0)
	{
		(*pos).x = (*pos).x + 2;
		(*pos).y = (*pos).y + num;
	}
	else if (i % 4 == 1)
	{
		
		(*pos).x = (*pos).x - 2;
		(*pos).y = (*pos).y + num;
	}
	else if (i % 4 == 2)
	{
		
		(*pos).x = (*pos).x + num;
		(*pos).y = (*pos).y + 2;
	}
	else
	{
		
		(*pos).x = (*pos).x + num;
		(*pos).y = (*pos).y - 2;
	}
	(*pos).x = (*pos).x + ((int [8])dir_x)[(map->iter - i + ((map->ori_x + i) % 2 == 0)) % 8];
	(*pos).y = (*pos).y + ((int [8])dir_y)[(map->iter - i + ((map->ori_y + i) % 2 == 1)) % 8];
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
				if (map->map[i - 2][j - 2] == '0')
				{
					//map->map[i - 2][j - 1] = '0';
					map->map[i - 1][j - 2] = '0';
					//map->map[i - 1][j - 1] = '0';
				}
				if (map->map[i + 2][j + 2] == '0')
				{
					//map->map[i + 2][j + 1] = '0';
					map->map[i + 1][j + 2] = '0';
					//map->map[i + 1][j + 1] = '0';
				}
				if (map->map[i - 2][j + 2] == '0')
				{
					//map->map[i - 2][j + 1] = '0';
					map->map[i - 1][j + 2] = '0';
					//map->map[i - 1][j + 1] = '0';
				}
				if (map->map[i + 2][j - 2] == '0')
				{
					//map->map[i + 2][j - 1] = '0';
					map->map[i + 1][j - 2] = '0';
					//map->map[i + 1][j - 1] = '0';
				}
			}
			j++;
		}
		i++;
	}
}

void	place_asset(t_map_simu *map, t_pointlist *p)
{
	if (p->len == 0 || p->len == 1)
		return ;
	for (int iter = 1; iter < p->len; iter++)
	{
		t_point prev = p->point[iter - 1];
		t_point pos = p->point[iter];

		while (prev.x < pos.x || prev.y < pos.y)
		{
        	if (prev.y < pos.y)
			{
				map->count++;
				map->map[prev.x][++prev.y] = '0';
			}
        	if (prev.x < pos.x)
			{
				map->count++;
				map->map[++prev.x][prev.y] = '0';
			}
    	}
		while (prev.x > pos.x || prev.y > pos.y)
		{
        	if (prev.y > pos.y)
			{
				map->count++;
				map->map[prev.x][--prev.y] = '0';
			}
        	if (prev.x > pos.x)
			{
				map->count++;
				map->map[--prev.x][prev.y] = '0';
			}
		}
	}
}

void	place_struct(t_map_simu *map, char *seed)
{
	int	i;
	int	j;
	int	index;
	int	len;

	i = 0;
	len = ft_strlen(seed);
	index = 0;
	while (i <= map->height)
	{
		j = 0;
		while (j <= map->width)
		{
			if (map->map[i][j] == '0' && nb_zero_neighbour(map, i, j) >= 6
				&& seed[(len + index++) % len] == '1')
				map->map[i][j] = '1';
			j++;
		}
		i++;
	}
}

void	gen_map_algo(t_map_simu *map, char *seed, t_point pos, int total)
{
	int			i;
	size_t		index;
	t_pointlist	*list;

	i = 0;
	index = 0;
	(void)index;
	(void)seed;
	list = initpoints(map->iter *2);
	if (!list)
		return ;
	while (i < map->iter)
	{
		if ((pos.x < map->height && pos.x >= 0)
			&& (pos.y < map->width && pos.y >= 0))
		{
			if (map->map[pos.x][pos.y] == '0')
			{
				if (addpoint(list, pos) < 0)
				{
					place_asset(map, list);
					free_pointlist(list);
					return ;
				}
				pos.x += ((int [8])dir_x)[(map->iter - variant_gen_x) % 8];
				pos.y += ((int [8])dir_y)[(map->iter - variant_gen_y) % 8];
				if (++total == map->iter)
				{
					free_pointlist(list);
					return ;
				}
				if ((pos.x < map->height && pos.x >= 0) && (pos.y < map->width && pos.y >= 0))
				{
					if (addpoint(list, pos) < 0)
					{
						place_asset(map, list);
						free_pointlist(list);
						return ;
					}
				}
				continue ;
			}
			map->map[pos.x][pos.y] = seed[(ft_strlen(seed) + index++)
				% ft_strlen(seed)];
			
			map->count++;
			if (addpoint(list, pos) < 0)
			{
				place_asset(map, list);
				free_pointlist(list);
				return ;
			}
			place_asset(map, list);
			resetpointlist(list);
		}
		else
		{
			pos.x = map->ori_x;
			pos.y = map->ori_y;
		}
		if (addpoint(list, pos) < 0)
		{
			place_asset(map, list);
			free_pointlist(list);
			return ;
		}
		l_shape(&pos, i, map);
		if ((pos.x < map->height && pos.x >= 0) && (pos.y < map->width && pos.y >= 0))
		{
			if (addpoint(list, pos) < 0)
			{
				place_asset(map, list);
				free_pointlist(list);
				return ;
			}
		}
		i++;
	}
	free_pointlist(list);
}

bool	generate_map(t_map_simu *map, long int seed)
{
	char	*str_seed;
	const t_point	val = {.x = map->ori_x,
		.y = map->ori_y};

	str_seed = ft_calloc(sizeof(char), 65);
	if (!str_seed)
	{
		free_t_map_simu(map);
		throw_error_bonus(ERR_MALLOC_BNS);
		return (false);
	}
	int_to_bin_str(seed, (char *)str_seed);
	gen_map_algo(map, str_seed, val, 0);
	link_zero(map);
	place_struct(map, str_seed);
	apply_wall(map);
	//place_door(map);
	free(str_seed);
	if (map_empty(map))
	{
		debug_seed(map, seed, 0);
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
	int			i;


	data = ft_calloc(sizeof(t_data), 1);
	if (!data)
	{
		throw_error(ERROR_MALLOC);
		return (NULL);
	}
	map = seed_to_mapsimu(seed);
	map->map = ft_calloc(map->height + 1, sizeof(char *));
	i = 0;
	while (i <= map->height)
	{
		map->map[i] = ft_calloc(sizeof(char), map->width + 1);
		ft_memset(map->map[i], ' ', map->width);
		i++;
	}
	if (!generate_map(map, seed))
	{
		free(data);
		return (NULL);
	}
	map->spawn = (t_int3){.zero = -1, .one = 0,
		.two = "NSEW"[add_digit_number(seed) % 4]};
	if (!map->map)
	{
		throw_error_bonus(ERR_MALLOC_BNS);
		free_t_map_simu(map);
		free(data);
		return (NULL);
	}
	if (place_spawn(map) == 0)
	{
		throw_error_bonus(MAP_NO_SPAWN);
		free_t_map_simu(map);
		free(data);
		return (NULL);
	}
	debug_seed(map, seed, 0);
	debug_seed(map, seed, 1);
	data->map = convert_map_simu_to_map(map);
	return (data);
}