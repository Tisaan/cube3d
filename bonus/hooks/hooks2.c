/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 15:54:55 by tseche            #+#    #+#             */
/*   Updated: 2026/06/09 16:28:34 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	update_mouse_rot(t_data *d)
{
	int	x;
	int	y;

	mlx_mouse_get_pos(d->mlx, &x, &y);
	if (x != (int)d->mouse_pos->x)
	{
		if (x > d->mouse_pos->x)
		{
			rotate_vect(&d->player->dir, d->delta * PLAYER_ROT_SPEED);
			rotate_vect(&d->player->camera, d->delta * PLAYER_ROT_SPEED);
		}
		else
		{
			rotate_vect(&d->player->dir, -(d->delta * PLAYER_ROT_SPEED));
			rotate_vect(&d->player->camera, -(d->delta * PLAYER_ROT_SPEED));
		}
		mlx_mouse_move(d->mlx, d->win, WIN_HEIGHT / 2,  WIN_WIDTH / 2);
	}
}