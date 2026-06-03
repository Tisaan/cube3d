/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 18:30:15 by pcaplat           #+#    #+#             */
/*   Updated: 2026/06/03 12:35:44 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/player.h"
#include "../includes/cub3d.h"

static void	set_player_orientation(t_player *player, t_direction_id dir)
{
	if (dir == NO || dir == 'N')
	{
		set_vect(&player->dir, 0, -1);
		set_vect(&player->camera, 0.66, 0);
	}
	else if (dir == SO || dir == 'S')
	{
		set_vect(&player->dir, 0, 1);
		set_vect(&player->camera, -0.66, 0);
	}
	else if (dir == WE || dir == 'W')
	{
		set_vect(&player->dir, -1, 0);
		set_vect(&player->camera, 0, -0.66);
	}
	else if (dir == EA || dir == 'E')
	{
		set_vect(&player->dir, 1, 0);
		set_vect(&player->camera, 0, 0.66);
	}
}

int	init_player(t_data *data)
{
	data->player = malloc(sizeof(t_player) * 1);
	if (!data->player)
		return (-ERROR_MALLOC);
	data->player->size = WALL_SIZE / 2;
	data->player->pos.x = data->map->start[1] * WALL_SIZE + WALL_SIZE / 2.0f;
	data->player->pos.y = data->map->start[0] * WALL_SIZE + WALL_SIZE / 2.0f;
	set_player_orientation(data->player, data->map->start[2]);
	return (NO_ERROR);
}
