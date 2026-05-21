/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 17:42:13 by tseche            #+#    #+#             */
/*   Updated: 2026/05/21 21:18:10 by tseche           ###   ########.fr       */
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
	for (int i = 2; i < map->height - 2; i++)
	{
		for (int j = 2; j < map->width - 2; j++)
		{
			if (map->map[i][j] == '0'){
				if (map->map[i - 2][j] == '0')
					map->map[i - 1][j] = '0';
				if (map->map[i + 2][j] == '0')
					map->map[i + 1][j] = '0';
				if (map->map[i][j - 2] == '0')
					map->map[i][j - 1] = '0';
				if (map->map[i][j + 2] == '0')
					map->map[i][j + 1] = '0';
			}
		}
	}
}

void	generate_map(t_map_simu *map, long int seed)
{
	char	*str_seed = ft_calloc(sizeof(char), 65);
	int			pos[2];
	const int	dir_x[8] = {1, -1, 1, 0, 0, -1, 1, -1};
	const int	dir_y[8] = {-1, 1, -1, 0, 0, 1, -1, 1};
	int			i;
	int			total;
	size_t			index;

	i = 0;
	total = 0;
	pos[0] = map->ori_x;
	pos[1] = map->ori_y;
	index = 0;
	int_to_bin_str(seed, (char *)str_seed);
	while (i < map->iter)
	{
		if (index >= ft_strlen(str_seed))
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
			map->map[pos[0]][pos[1]] = str_seed[index++];
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
	link_zero(map);
	apply_wall(map);
	place_door(map);
	free(str_seed);
}

int	main(void)
{
	const long int	seed = gen_seed();
 	t_map_simu		*map;

	map = seed_to_mapsimu(seed);
	debug_seed(map, seed, 0);
	map->map = ft_calloc(map->height + 1, sizeof(int *));
	for (int i = 0; i <= map->height; i++)
	{
		map->map[i] = ft_calloc(sizeof(int), map->width + 1);
		ft_memset(map->map[i], ' ', map->width);
	}
	generate_map(map, seed);
	if (map_empty(map))
	{
		throw_error_bonus(MAP_EMPTY_GEN);
		free_t_map_simu(map);
		return (1);
	}
	// changer pour trouver le 0 le plus proche car peux etre en dehors de la gene
	map->map[map->ori_x][map->ori_y] = "NSEW"[add_digit_number(seed) % 4];
	debug_seed(map, seed, 1);

	t_two_group result = find_biggest_groups(map, map->height);

    printf("1st largest '0' group (size: %d)\n", result.first.count);
    for (int i = 0; i < result.first.count; i++)
        printf("(%d,%d) ", result.first.coords[i].row, result.first.coords[i].col);
    printf("\n");

    printf("2nd largest '0' group (size: %d)\n", result.second.count);
    for (int i = 0; i < result.second.count; i++)
        printf("(%d,%d) ", result.second.coords[i].row, result.second.coords[i].col);
    printf("\n");

    free_group(&result.first);
    free_group(&result.second);
	free_t_map_simu(map);
}