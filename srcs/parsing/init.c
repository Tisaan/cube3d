/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 11:56:21 by pcaplat           #+#    #+#             */
/*   Updated: 2026/05/12 21:09:22 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/debug.h"

void	init_map_data(t_data *data)
{
	data->texture[0].path = NULL;
	data->texture[1].path = NULL;
	data->texture[2].path = NULL;
	data->texture[3].path = NULL;
	data->plans_color[0].type = EMPT;
	data->plans_color[1].type = EMPT;
}

static void	set_img_pixel(t_data *data, mlx_image img, mlx_color color)
{
	int			x;
	int			y;

	y = 0;
	while (y < WALL_SIZE - 1)
	{
		x = 0;
		while (x < WALL_SIZE - 1)
		{
			mlx_set_image_pixel(data->mlx, img, x, y, color);
			x++;
		}
		y++;
	}
}

int	init_game(t_data *data)
{
	int	ret;
	mlx_color	color;

	ret = init_player(data);
	if (ret < 0)
		return (ret);
	display_player_data(data->player);
	data->wall_assets[0] = mlx_new_image(data->mlx, WALL_SIZE, WALL_SIZE);
	if (data->wall_assets[0] == MLX_NULL_HANDLE)
		return (-ERROR_LOAD_ASSET);
	data->floor_asset = mlx_new_image(data->mlx, WALL_SIZE, WALL_SIZE);
	if (data->floor_asset == MLX_NULL_HANDLE)
		return (-ERROR_LOAD_ASSET);
	data->frame = mlx_new_image(data->mlx, data->win_infos.width, data->win_infos.height);
	color.rgba = 0xFFFFFFFF;
	set_img_pixel(data, data->wall_assets[0], color);
	color.r = 0;
	color.g = 0;
	color.b = 0;
	color.a = 1;
	set_img_pixel(data, data->floor_asset, color);
	return (NO_ERROR);
}
