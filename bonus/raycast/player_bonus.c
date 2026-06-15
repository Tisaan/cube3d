/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 18:30:15 by pcaplat           #+#    #+#             */
/*   Updated: 2026/06/15 14:05:22 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/player_bonus.h"
#include "../includes/cub3d_bonus.h"

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
	int	ret;

	data->player = malloc(sizeof(t_player) * 1);
	if (!data->player)
		return (-ERROR_MALLOC);
	data->player->size = WALL_SIZE / 2;
	data->player->pos.x = data->map->start[1] * WALL_SIZE + WALL_SIZE / 2.0f;
	data->player->pos.y = data->map->start[0] * WALL_SIZE + WALL_SIZE / 2.0f;
	set_player_orientation(data->player, data->map->start[2]);
	if (init_mouse(data) < 0)
		return (-ERROR_MALLOC);
	ret = init_player_sprite(data);
	if (ret < 0)
		return (ret);
	data->player->sprite.frame = 0;
	data->player->sprite.is_playing = false;
	set_sprite_scale(data->win_infos, &data->player->sprite);
	set_sprite_pos(data->win_infos, &data->player->sprite);
	data->player->can_shoot = true;
	return (NO_ERROR);
}
