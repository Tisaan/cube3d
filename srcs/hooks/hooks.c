/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 10:53:19 by tseche            #+#    #+#             */
/*   Updated: 2026/05/19 11:14:35 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../includes/cub3d.h"

// static void	movement_hooks(int key, t_data *data)
// {
// 	t_vect	new_pos;
// 	int		tile_x;
// 	int		tile_y;
// 	float	save_dir;
//
// 	data->player->speed = data->delta * 200.0f;
// 	printf("player before (%f, %f)\tspeed: %f\n", data->player->pos.x, data->player->pos.y, data->player->speed);
// 	data->player->rot_speed = data->delta * 3.0;
// 	if (key == W_KEY || key == UP)
// 	{
// 		new_pos.x = data->player->pos.x + data->player->dir.x * data->player->speed;
// 		new_pos.y = data->player->pos.y;
// 		tile_x = (int)(data->player->pos.x + data->player->dir.x * data->player->speed) / WALL_SIZE;
// 		tile_y = (int)(data->player->pos.y) / WALL_SIZE;
// 		if (data->map->grid[tile_y][tile_x] == '0')
// 		{
// 			printf("not collinding\n");
// 			data->player->pos.x = new_pos.x;
// 		}
// 		tile_x = (int)(data->player->pos.x) / WALL_SIZE;
// 		tile_y = (int)(data->player->pos.y - data->player->dir.y * data->player->speed) / WALL_SIZE;
// 		if (data->map->grid[tile_y][tile_x] == '0')
// 			data->player->pos.y = new_pos.y;
// 		printf("Up is working : (%f, %f)\n", new_pos.x, new_pos.y);
// 	}
// 	else if (key == S_KEY || key == DOWN)
// 	{
// 		new_pos.x = data->player->pos.x - data->player->dir.x * data->player->speed;
// 		new_pos.y = data->player->pos.y - data->player->dir.y * data->player->speed;
// 		tile_x = (int)(data->player->pos.x - data->player->dir.x * data->player->speed) / WALL_SIZE;
// 		tile_y = (int)(data->player->pos.y) / WALL_SIZE;
// 		if (data->map->grid[tile_x][tile_y])
// 			data->player->pos.x = new_pos.x;
// 		tile_x = (int)(data->player->pos.x) / WALL_SIZE;
// 		tile_y = (int)(data->player->pos.y - data->player->dir.y * data->player->speed) / WALL_SIZE;
// 		if (data->map->grid[tile_y][tile_x] == '0')
// 			data->player->pos.y = new_pos.y;
// 		printf("DOWN\n");
// 	}
//
// 	else if (key == A_KEY || key == LEFT)
// 	{
// 		save_dir = data->player->dir.x;
// 		data->player->dir.x = data->player->dir.x * cosf(data->player->rot_speed) - data->player->dir.y * sinf(data->player->rot_speed);
// 		data->player->dir.y = save_dir * sinf(data->player->rot_speed) + data->player->dir.y * cosf(data->player->rot_speed);
// 		save_dir = data->player->camera.x;
// 		data->player->camera.x = data->player->camera.x * cosf(data->player->rot_speed) - data->player->camera.y * sinf(data->player->rot_speed);
// 		data->player->camera.y = save_dir * sinf(data->player->rot_speed) + data->player->camera.y	* cosf(data->player->rot_speed);
// 	}
// 	else if (key == D_KEY || key == RIGHT)
// 	{
// 		save_dir = data->player->dir.x;
// 		data->player->dir.x = data->player->dir.x * cosf(-data->player->rot_speed) - data->player->dir.y * sinf(-data->player->rot_speed);
// 		data->player->dir.y = save_dir * sinf(-data->player->rot_speed) + data->player->dir.y * cosf(-data->player->rot_speed);
// 		save_dir = data->player->camera.x;
// 		data->player->camera.x = data->player->camera.x * cosf(-data->player->rot_speed) - data->player->camera.y * sinf(-data->player->rot_speed);
// 		data->player->camera.y = save_dir * sinf(-data->player->rot_speed) + data->player->camera.y	* cosf(-data->player->rot_speed);
// 	}
// 	else
// 		return ;
// 	// printf("player (%f, %f)\n", data->player->pos.x, data->player->pos.y);
// }

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
	// movement_hooks(key, data);
}

void	window_hook(int event, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (event == WIN_CLOSE)
		mlx_loop_end(data->mlx);
}
