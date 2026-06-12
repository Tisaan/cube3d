/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_animation_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat </var/spool/mail/pcaplat>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 13:31:29 by pcaplat           #+#    #+#             */
/*   Updated: 2026/06/12 14:22:08 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_sprite_pos(t_win_infos win, t_animated_sprite_2d *sprite)
{
	sprite->x = (win.width / 2) - (sprite->width / 2);
	sprite->y = win.height - sprite->height;
	printf("sprite pos(%d, %d)\n", sprite->x, sprite->y);
}
