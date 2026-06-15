/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 14:29:30 by pcaplat           #+#    #+#             */
/*   Updated: 2026/06/15 13:59:06 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"
#include "../includes/bonus.h"
#include "../includes/mini_map_bonus.h"

int	fill_start_with_space(t_map *map, int *i, int *map_y)
{
	while (*map_y < 0)
	{
		map->viewport[*i] = ft_strdup("           ");
		if (!map->viewport[*i])
		{
			clear_viewport(map, *i);
			return (-ERROR_MALLOC);
		}
		*i += 1;
		*map_y += 1;
	}
	return (NO_ERROR);
}

int	fill_end_with_space(t_map *map, int *i)
{
	while (*i < 11)
	{
		map->viewport[*i] = ft_strdup("           ");
		if (!map->viewport[*i])
		{
			clear_viewport(map, *i);
			return (-ERROR_MALLOC);
		}
		*i += 1;
	}
	return (NO_ERROR);
}

int	set_viewport(t_player *player, t_map *map)
{
	t_point	view_pos;

	map->viewport = malloc(sizeof(char *) * (11 + 1));
	if (!map->viewport)
		return (-ERROR_MALLOC);
	view_pos.x = (int)(player->pos.x / WALL_SIZE) - 5;
	view_pos.y = (int)(player->pos.y / WALL_SIZE) - 5;
	if (fill_viewport(player, map, view_pos) < 0)
		return (-ERROR_MALLOC);
	return (NO_ERROR);
}
