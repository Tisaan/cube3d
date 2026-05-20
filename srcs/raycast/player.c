/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 18:30:15 by pcaplat           #+#    #+#             */
/*   Updated: 2026/05/20 17:20:55 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/player.h"
#include "../../includes/cub3d.h"

static void	set_player_orientation(t_player *player, t_direction_id dir)
{
	if (dir == NO)
	{
		set_vect(&player->dir, 0, -1);
		set_vect(&player->camera, 0.66, 0);
	}
	else if (dir == SO)
	{
		set_vect(&player->dir, 0, 1);
		set_vect(&player->camera, -0.66, 0);
	}
	else if (dir == WE)
	{
		set_vect(&player->dir, -1, 0);
		set_vect(&player->camera, 0, -0.66);
	}
	else if (dir == EA)
	{
		set_vect(&player->dir, 1, 0);
		set_vect(&player->camera, 0, 0.66);
	}
}

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

	//debug
	color.rgba = 0x0000FFFF;
	for (int y = 0; y < 32; y++)
		for (int x = 0; x < 32; x++)
			mlx_set_image_pixel(data->mlx, data->player->sprite, x, y, color);

	data->player->size = WALL_SIZE / 2;
	data->player->pos.x = data->map->start[1] * WALL_SIZE + WALL_SIZE / 2.0f;
	data->player->pos.y = data->map->start[0] * WALL_SIZE + WALL_SIZE / 2.0f;
	for (int i = 0; data->map->grid[i]; i++)
		printf("[%d]: '%s' (len=%zu)\n", i, data->map->grid[i], ft_strlen(data->map->grid[i]));
	set_player_orientation(data->player, data->map->start[2]);
	return (NO_ERROR);
}
