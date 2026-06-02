/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 18:30:15 by pcaplat           #+#    #+#             */
/*   Updated: 2026/05/06 19:23:19 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/player.h"
#include "../../includes/cub3d.h"

int	init_player(t_data *data)
{
	data->player = malloc(sizeof(t_player) * 1);
	if (!data->player)
		return (-ERROR_MALLOC);
	data->player->aov = (float)(data->map->start[2]);
	data->player->fov = FOV_ANGLE;
	data->player->size = WALL_SIZE / 2;
	data->player->pos.x = data->map->start[0];
	data->player->pos.y = data->map->start[1];
	return (NO_ERROR);
}
