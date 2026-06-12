/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_animation_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat </var/spool/mail/pcaplat>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 13:31:29 by pcaplat           #+#    #+#             */
/*   Updated: 2026/06/12 16:03:51 by pcaplat          ###   ########.fr       */
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

void	start_shoot_animation(t_data *data)
{
	t_animated_sprite_2d	*sprite;

	sprite = &data->player->sprite;
	sprite->anim_time = 0.0f;
	sprite->is_playing = true;
}

void	update_sprite_frame(t_data *data)
{
	t_animated_sprite_2d	*sprite;

	sprite = &data->player->sprite; 
	if (!sprite->is_playing)
		return ;
	sprite->anim_time += data->delta;
	sprite->frame = (int)(sprite->anim_time / ANIM_SPEED);
	if (sprite->frame >= SPRITE_FRAMES)
	{
		sprite->frame = 0;
		sprite->anim_time = 0.0f;
		sprite->is_playing = false;
		data->player->can_shoot = true;
	}
}
