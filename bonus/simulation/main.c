/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 17:42:13 by tseche            #+#    #+#             */
/*   Updated: 2026/05/15 18:15:13 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus.h"

void	int_to_bin_str(unsigned long num, char *s)
{
	unsigned long	mask;
	int				index;

	if (num == 0)
	{
		ft_strcpy(s, "0", 1);
		return ;
	}
	mask = 1UL << (sizeof(unsigned long) * 8 - 1);
	index = 0;
	while ((num & mask) == 0)
		mask >>= 1;
	while (mask != 0){
		if (num & mask)
			s[index++] = '1';
		else
			s[index++] = '0';
		mask >>= 1;
	}
	s[index] = '\0';
}

void l_shape(int *pos, int i){
	const int 	table[3] = {-1, 0, 1};
	int			num;
	int			sum;

	num = table[i % 3];
	if (i % 4 == 0)
	{
		sum = pos[0] + 2 + pos[1] + num;
		pos[0] = pos[0] + 2;
		pos[1] = pos[1] + num;
	}
	else if (i % 4 == 1)
	{
		sum = pos[0] - 2 + pos[1] + num;
		pos[0] = pos[0] - 2;
		pos[1] = pos[1] + num;
	}
	else if (i % 4 == 2)
	{
		sum = pos[0] + num + pos[1] + 2;
		pos[0] = pos[0] + num;
		pos[1] = pos[1] + 2;
	}
	else
	{
		sum = pos[0] + num + pos[1] - 2;
		pos[0] = pos[0] + num;
		pos[1] = pos[1] - 2;
	}
}

void generate_map(long seed, t_map_simu *map){
	char	*str_seed = ft_calloc(sizeof(char), 65);
    int 	pos[2] = {map->ori_x, map->ori_y};
    int 	dir_x[8] = {1, -1, 1, 0, 0, -1, 1, -1}; // moore-neighboorhood
	int 	dir_y[8] = {-1, 1, -1, 0, 0, 1, -1, 1};
	size_t	len;

    int_to_bin_str(seed, (char *)str_seed);
    size_t index = 0;
    int i = 0;
	len = ft_strlen(str_seed);
    while (i < map->iter)
	{
        if (index >= len)
            index = 0; 
        if ((pos[0] < map->height && pos[0] >= 0) &&
			(pos[1] < map->width && pos[1] >= 0)){
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
	free(str_seed);
	apply_wall(map);
}


int main()
{
	long int			seed = gen_seed(100000000000, 999999999999);
	t_map_simu	*map = seed_to_mapsimu(seed);

	debug_seed(map, seed);
	map->map = ft_calloc(map->height + 1, sizeof(int *));
	for (int i = 0; i <= map->height; i++)
	{
		map->map[i] = ft_calloc(sizeof(int), map->width + 1);
		ft_memset(map->map[i], ' ', map->width);
	}
	
	generate_map(seed, map);
	printf("map:\n");
	for (int i = 0; i <= map->height; i++)
		printf("%s\n", map->map[i]);
	// printf("end\n");
	// simulate(map);
	// printf("map:\n");
	// for (int i = 0; i <= map->height; i++)
	// 	printf("%s\n", map->map[i]);
	// printf("end\n");
	// int			*spoint = spawn(map);
	// printf("spawn[%d]\n", spoint[0]);
	// if (spoint[0] == -1)
	// 	printf("no spawn found\n");
	// else
	// 	map->map[spoint[0]][spoint[1]] = "NSEW"[spoint[2]];
	
	for (int i = 0; i <= map->height; i++)
		free(map->map[i]);
	// free(spoint);
	free(map->map);
	free(map);
}