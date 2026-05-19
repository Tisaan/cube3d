/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 10:53:19 by tseche            #+#    #+#             */
/*   Updated: 2026/05/19 13:28:13 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../includes/cub3d.h"	

static void	normalize(t_vect *vect, float speed)
{
	float	lenght;

	lenght = sqrtf(vect->x * vect->x + vect->y * vect->x); 
	if (lenght > speed)
	{
		vect->x = vect->x / lenght * speed;
		vect->y = vect->y / lenght * speed;
	}
}

static void	movement_hooks(int key, void *param)
{
	t_data		*data;
	t_player	*p;
	float		speed;

	data = (t_data *)param;
	p = data->player;
	speed = data->delta * PLAYER_SPEED;
	set_vect(&p->dest, 0.0f, 0.0f);
	if (key == W_KEY)
	{
		p->dest.x += p->dir.x * speed;
		p->dest.y += p->dir.y * speed;
	}
	if (key == S_KEY)
	{
		p->dest.x -= p->dir.x * speed;
		p->dest.y -= p->dir.y * speed;
	}
	if (key == D_KEY)
	{
		p->dest.x += -p->dir.y * speed;
		p->dest.y += p->dir.x * speed;
	}	
	if (key == A_KEY)
	{
		p->dest.x -= -p->dir.y * speed;
		p->dest.y -= p->dir.x * speed;
	}
	normalize(&p->dest, speed);
	printf("dest(%f, %f)\n", p->dest.x, p->dest.y);
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
