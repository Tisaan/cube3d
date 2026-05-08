/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 17:42:13 by tseche            #+#    #+#             */
/*   Updated: 2026/05/07 18:35:07 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus.h"

int main()
{
	int	range[2];
	get_range(range, 1, NULL);
	int			seed = gen_seed(range[0], range[1]);
	t_map_simu	*map = seed_to_mapsimu(seed);
	map->map = ft_calloc(map->height, sizeof(int *));
	for (int i = 0; i < map->height; i++)
		map->map[i] = ft_calloc(sizeof(int), map->width);
	simulate(map);
	char **nmap = get_map_from_simu(map);
	int			*spoint = spawn(map);
	nmap[spoint[0]][spoint[1]] = "NSEW"[spoint[2]];
}