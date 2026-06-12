/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_img_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat </var/spool/mail/pcaplat>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 13:17:10 by pcaplat           #+#    #+#             */
/*   Updated: 2026/06/12 13:29:49 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	destroy_sprite_assets(t_data *data)
{
	int						i;
	t_animated_sprite_2d	*sprite;

	sprite = &data->player->sprite;
	i = 0;
	while (i < SPRITE_FRAMES)
	{
		if (sprite->spritesheet[i] != MLX_NULL_HANDLE)
			mlx_destroy_image(data->mlx, sprite->spritesheet[i]);
		i++;
	}
	free(sprite->spritesheet);
}
