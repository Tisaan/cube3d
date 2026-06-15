/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: von <von@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 16:02:56 by pcaplat           #+#    #+#             */
/*   Updated: 2026/06/15 14:04:21 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	update_player_rot(void *param)
{
	t_data	*data;
	float	rot;

	data = (t_data *)param;
	rot = data->delta * PLAYER_ROT_SPEED;
	if (data->keys.right)
	{
		rotate_vect(&data->player->dir, rot);
		rotate_vect(&data->player->camera, rot);
	}
	if (data->keys.left)
	{
		rotate_vect(&data->player->dir, -rot);
		rotate_vect(&data->player->camera, -rot);
	}
}
