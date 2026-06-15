/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4_gen_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 18:15:28 by tseche            #+#    #+#             */
/*   Updated: 2026/06/15 14:39:10 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bonus.h"

bool	place_bound(
	t_map_simu *map,
	t_point *pos,
	int *index,
	t_pointlist *list
){
	size_t	len;

	len = ft_strlen(map->seed);
	map->map[pos->x][pos->y] = map->seed[(len + (*index)++)
		% len];
	if (!addpointfree(list, *pos, map))
		return (true);
	place_point_loop(map, list);
	resetpointlist(list);
	return (false);
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
