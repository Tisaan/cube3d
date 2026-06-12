/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 10:53:19 by tseche            #+#    #+#             */
/*   Updated: 2026/06/12 15:29:01 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../includes/cub3d.h"	
#include "../includes/raycast.h"

static void	movement_hooks(int key, t_data *data)
{
	if (key == W_KEY)
		data->keys.w = true;
	else if (key == A_KEY)
		data->keys.a = true;
	else if (key == S_KEY)
		data->keys.s = true;
	else if (key == D_KEY)
		data->keys.d = true;
	else if (key == LEFT)
		data->keys.left = true;
	else if (key == RIGHT)
		data->keys.right = true;
	else if (key == E_KEY)
		data->keys.e = true;
}

void	key_up_hook(int key, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (key == W_KEY)
		data->keys.w = false;
	else if (key == S_KEY)
		data->keys.s = false;
	else if (key == A_KEY)
		data->keys.a = false;
	else if (key == D_KEY)
		data->keys.d = false;
	else if (key == LEFT)
		data->keys.left = false;
	else if (key == RIGHT)
		data->keys.right = false;
	else if (key == E_KEY)
		data->keys.e = false;
	else if (key == F_KEY)
		data->keys.f = false;
}

void	key_hooks(int key, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (key == Q_KEY || key == ESC_KEY)
		mlx_loop_end(data->mlx);
	else if (key == F_KEY)
	{
		if (data->player->can_shoot)
			start_shoot_animation(data);
		data->player->can_shoot = false;
		data->keys.f = true;
	}
	else if (key == F3_KEY)
	{
		if (data->keys.f3 == true)
			data->keys.f3 = false;
		else
		 data->keys.f3 = true;
	}
	display_game_infos(data);
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
