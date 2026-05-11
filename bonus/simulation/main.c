/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 17:42:13 by tseche            #+#    #+#             */
/*   Updated: 2026/05/11 17:44:21 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus.h"



int main()
{
	int	range[2];
	get_range(range, 0, NULL);
	int			seed = gen_seed(range[0], range[1]);
	t_map_simu	*map = seed_to_mapsimu(seed);
	map->map = ft_calloc(map->height + 1, sizeof(int *));
	debug_seed(map);
	for (int i = 0; i < map->height; i++)
	{
		map->map[i] = ft_calloc(sizeof(int), map->width + 1);
		for (int j = 0; j < map->width; j++)
		{
			if ((j + i) % 2 == 1)
				map->map[i][j] = ' ';
		}
	}

	int	nb = map->stof + map->ftof + map->ftow;
	int i = -2;
	printf("nb: %d\n", nb);
	while (i <= 2)
	{
		int j = -2;
		while (j <= 2)
		{
			if (nb > 0)
			{
				map->map[(map->height / 2) + i][(map->width / 2) + j] = '0';
				nb--;
			}
			else 
				break ;
			j++;
		}
		i++;
	}
	printf("map:\n");
	for (int i = 0; map->map[i]; i++)
		printf("%s\n", map->map[i]);
	printf("end\n");
	simulate(map);
	printf("map:\n");
	for (int i = 0; map->map[i]; i++)
		printf("%s\n", map->map[i]);
	printf("end\n");
	//int			*spoint = spawn(map);
	//printf("spawn[%d]\n", spoint[0]);
	// if (spoint[0] == -1)
	// 	printf("no spawn found\n");
	// else
	// 	map->map[spoint[0]][spoint[1]] = "NSEW"[spoint[2]];
	
	for (int i = 0; i < map->height; i++)
		free(map->map[i]);
	free(map->map);
	free(map);
}