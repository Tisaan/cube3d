/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 10:53:19 by tseche            #+#    #+#             */
/*   Updated: 2026/05/10 10:16:31 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#ifndef SPEED
# define  SPEED	5
#endif

#include "../../includes/cub3d.h"

static bool	is_colliding (t_player *player, t_vect velocity, t_map *map)
{
	int			px;
	int			py;

	py = player->pos.y;
	px = player->pos.x;
	printf("map_w: %d, map_h: %d\n", map->width, map->height);
	if (px + velocity.x > map->width * WALL_SIZE)
		return (true);
	if (py + velocity.y > map->height * WALL_SIZE)
		return (true);
	py = (py + velocity.y * SPEED) / WALL_SIZE;
	px = (px + velocity.x * SPEED) / WALL_SIZE;
	printf("new_pos(%d, %d)\n", px, py);
	if (map->grid[py][px] == '1')
		return (true);
	return (false);
}

static void	movement_hooks(int key, t_data *data)
{
	t_vect		velocity;

	set_vect(&velocity, 0, 0);
	if (key == W_KEY || key == UP)
		velocity.y -= 1;
	if (key == S_KEY || key == DOWN)
		velocity.y += 1;
	if (key == A_KEY || key == LEFT)
		velocity.x -= 1;
	if (key == D_KEY || key == RIGHT)
		velocity.x += 1;
	if ((velocity.x != 0 || velocity.y != 0) && !is_colliding(data->player, velocity, data->map))
	{
		velocity = vect_multiply(velocity, SPEED);
		data->player->pos = vect_sum(data->player->pos, velocity);
	}
}

void	key_hooks(int key, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (key == Q_KEY || key == ESC_KEY)
		mlx_loop_end(data->mlx);
	else if (key == F_KEY)
	{
		if (data->win_infos.is_fullscreen == false)
		{
			data->win_infos.is_fullscreen = true;
			mlx_set_window_fullscreen(data->mlx, data->win, true);
		}
		else
		{
			data->win_infos.is_fullscreen = false;
			mlx_restore_window(data->mlx, data->win);
			mlx_set_window_fullscreen(data->mlx, data->win, false);
		}
	}
	movement_hooks(key, data);
}

void	window_hook(int event, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (event == WIN_CLOSE)
		mlx_loop_end(data->mlx);
}
