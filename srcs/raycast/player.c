/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 18:30:15 by pcaplat           #+#    #+#             */
/*   Updated: 2026/05/09 10:13:10 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/player.h"
#include "../../includes/cub3d.h"

int	init_player(t_data *data)
{
	mlx_color	color;

	data->player = malloc(sizeof(t_player) * 1);
	if (!data->player)
		return (-ERROR_MALLOC);
	data->player->sprite = mlx_new_image(data->mlx, 32, 32);
	if (data->player->sprite == MLX_NULL_HANDLE)
	{
		free(data->player);
		return (-ERROR_MALLOC);
	}
	color.rgba = 0x0000FFFF;
	for (int y = 0; y < 32; y++)
		for (int x = 0; x < 32; x++)
			mlx_set_image_pixel(data->mlx, data->player->sprite, x, y, color);
	data->player->aov = (float)(data->map->start[2]);
	data->player->fov = FOV_ANGLE;
	data->player->size = WALL_SIZE / 2;
	data->player->pos.x = data->map->start[0];
	data->player->pos.y = data->map->start[1];
	return (NO_ERROR);
}
