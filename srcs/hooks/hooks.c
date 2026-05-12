/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 10:53:19 by tseche            #+#    #+#             */
/*   Updated: 2026/05/12 09:27:26 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#ifndef SPEED
# define  SPEED	10
#endif

#include "../../includes/cub3d.h"

static bool	is_colliding (t_player *player, t_vect direction, t_map *map)
{
	int	px;
	int	py;
	int	offset;

	py = player->pos.y;
	px = player->pos.x;
	offset = 0;
	if (direction.x == 1.0 || direction.y == 1.0)
		offset = player->size - 1;
	printf("dx: %f, dy: %f\n", direction.x, direction.y);
	if (player->pos.x + direction.x + offset > map->width * WALL_SIZE)
		return (true);
	if (player->pos.y + direction.y + offset > map->height * WALL_SIZE)
		return (true);
	py = (int)(py + offset + (direction.y * SPEED)) / WALL_SIZE;
	px = (int)(px + offset + (direction.x * SPEED)) / WALL_SIZE;
	printf("new_pos(%d, %d)\n", px, py);
	if (map->grid[py][px] == '1')
		return (true);
	return (false);
}

static void	movement_hooks(int key, t_data *data)
{
	set_vect(&data->player->dir, 0, 0);
	if (key == W_KEY || key == UP)
		data->player->dir.y -= 1;
	if (key == S_KEY || key == DOWN)
		data->player->dir.y += 1;
	if (key == A_KEY || key == LEFT)
		data->player->dir.x -= 1;
	if (key == D_KEY || key == RIGHT)
		data->player->dir.x += 1;
	if ((data->player->dir.x != 0 || data->player->dir.y != 0) && !is_colliding(data->player, data->player->dir, data->map))
	{
		data->player->dir = vect_multiply(data->player->dir, SPEED);
		data->player->pos = vect_sum(data->player->pos, data->player->dir);
	}
	printf("player after movement: (%f, %f)\n", data->player->pos.x, data->player->pos.y);
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
