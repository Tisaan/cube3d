/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 10:53:19 by tseche            #+#    #+#             */
/*   Updated: 2026/05/12 15:37:27 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#ifndef SPEED
# define  SPEED	10
#endif

#include "../../includes/cub3d.h"

// static void	movement_hooks(int key, t_data *data)
// {
// 	int	x;
// 	int	y;
//
// 	data->player->speed = data->delta * 5.0;
// 	data->player->rot_speed = data->delta * 3.0;
// 	if (key == W_KEY || key == UP)
// 	{
// 		x = (int)(data->player->pos.x + (data->player->dir.x * data->player->speed)) / WALL_SIZE;
// 		y = (int)(data->player->pos.y) / WALL_SIZE;
// 		if (data->map->grid[y][x] == '0')
// 			data->player->pos.x += data->player->dir.x * data->player->speed;
// 		y = (int)(data->player->pos.y + (data->player->dir.y * data->player->speed)) / WALL_SIZE;
// 		x = (int)(data->player->pos.x) / WALL_SIZE;
// 		if (data->map->grid[y][x] == '0')
// 			data->player->pos.y += data->player->dir.y * data->player->speed;
// 	}
// 	// if (key == S_KEY || key == DOWN)
// 	// if (key == A_KEY || key == LEFT)
// 	// if (key == D_KEY || key == RIGHT)
// 	// if ((data->player->dir.x != 0 || data->player->dir.y != 0))
// }
//
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
//	movement_hooks(key, data);
}

void	window_hook(int event, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (event == WIN_CLOSE)
		mlx_loop_end(data->mlx);
}
