/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 18:15:28 by tseche            #+#    #+#             */
/*   Updated: 2026/06/03 18:30:30 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bonus.h"

bool	place_bound(
	t_map_simu *map,
	t_point *pos,
	int *index,
	t_pointlist *list
){
	map->map[pos->x][pos->y] = map->seed[(ft_strlen(map->seed) + (*index)++)
		% ft_strlen(map->seed)];
	if (!addpointfree(list, *pos, map))
		return (true);
	place_point_loop(map, list);
	resetpointlist(list);
	return (false);
}
