/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: von <von@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 10:53:19 by tseche            #+#    #+#             */
/*   Updated: 2026/06/01 16:34:32 by von              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../includes/cub3d.h"	
#include "../includes/raycast.h"

static void	movement_hooks(int key, t_data *data)
{
	if (key == W_KEY)
		data->keys.w = true;
	if (key == A_KEY)
		data->keys.a = true;
	if (key == S_KEY)
		data->keys.s = true;
	if (key == D_KEY)
		data->keys.d = true;
	if (key == LEFT)
		data->keys.left = true;
	if (key == RIGHT)
		data->keys.right = true;
}

void	key_up_hook(int key, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (key == W_KEY)
		data->keys.w = false;
	if (key == S_KEY)
		data->keys.s = false;
	if (key == A_KEY)
		data->keys.a = false;
	if (key == D_KEY)
		data->keys.d = false;
	if (key == LEFT)
		data->keys.left = false;
	if (key == RIGHT)
		data->keys.right = false;
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

void	ray_hook(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	raycast(data, data->player);
}
