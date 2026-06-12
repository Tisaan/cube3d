/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_animation_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat </var/spool/mail/pcaplat>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 13:31:29 by pcaplat           #+#    #+#             */
/*   Updated: 2026/06/12 15:02:06 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_sprite_pos(t_win_infos win, t_animated_sprite_2d *sprite)
{
	int	target_w;
	int	target_h;

	target_w = (int)(win.width * SPRITE_RATIO);
	target_h = (int)(sprite->height * sprite->scale);
	sprite->x = (win.width / 2) - (target_w / 2);
	sprite->y = win.height - target_h;
}

void	set_sprite_scale(t_win_infos win, t_animated_sprite_2d *sprite)
{
	int	target_w;

	target_w = (int)(win.width * SPRITE_RATIO);
	sprite->scale = (float)target_w / (float)sprite->width;
}
