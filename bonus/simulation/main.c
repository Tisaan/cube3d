/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: von <von@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 17:42:13 by tseche            #+#    #+#             */
/*   Updated: 2026/05/18 15:51:26 by von              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus.h"

int main()
{
	long int			seed = gen_seed(100000000000, 999999999999);
	t_map_simu	*map = seed_to_mapsimu(seed);

	debug_seed(map, seed);
	map->map = ft_calloc(map->height + 1, sizeof(int *));
	for (int i = 0; i <= map->height; i++)
	{
		map->map[i] = ft_calloc(sizeof(int), map->width + 1);
		for (int j = 0; j < map->width; j++)
		{
			if (i % 2 == 1)
				map->map[i][j] = ' ';
			else
				map->map[i][j] = '0';
		}
		printf("%s\n", map->map[i]);
	}
	simulate(map);
	for (int i = 0; map->map[i]; i++)
		printf("%s\n", map->map[i]);
	//int			*spoint = spawn(map);
	//printf("spawn[%d]\n", spoint[0]);
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