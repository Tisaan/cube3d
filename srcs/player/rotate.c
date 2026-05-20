/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 16:02:56 by pcaplat           #+#    #+#             */
/*   Updated: 2026/05/19 16:12:20 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	update_player_rot(void *param)
{
	t_data	*data;
	float	rot;

	data = (t_data *)param;
	rot = data->delta * PLAYER_ROT_SPEED;
	if (data->keys.right)
	{
		rotate_vect(&data->player->dir, -rot);
		rotate_vect(&data->player->camera, -rot);
	}
	if (data->keys.left)
	{
		rotate_vect(&data->player->dir, rot);
		rotate_vect(&data->player->camera, rot);
	}
}
