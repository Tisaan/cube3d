/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 17:04:03 by pcaplat           #+#    #+#             */
/*   Updated: 2026/05/19 10:21:44 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/raycast.h"

// static void	render_player(t_data *data)
// { t_player	*player;
// 	int			px;
// 	int			py;
//
// 	player = data->player;
// 	px = (int)player->pos.x;
// 	py = (int)player->pos.y;
// 	mlx_put_image_to_window(data->mlx, data->win, player->sprite, px, py);
// }

// static void	render_2D_map(t_data *data)
// {
// 	// t_map		*map;
// 	// // int			x;
// 	// int			y;
// 	//
// 	// map = data->map;
// 	// y = 0;
// 	// while (map->grid[y])
// 	// {
// 	// 	x = 0;
// 	// 	while (map->grid[y][x])
// 	// 	{
// 	// 		if (map->grid[y][x] == '1')
// 	// 			mlx_put_image_to_window(data->mlx, data->win, data->wall_assets[0], x * WALL_SIZE, y * WALL_SIZE);
// 	// 		else
// 	// 			mlx_put_image_to_window(data->mlx, data->win, data->floor_asset, x * WALL_SIZE, y * WALL_SIZE);
// 	// 		x++;
// 	// 	}
// 	// 	y++;
// 	// }
// }

void	render(void *param)
{
	t_data		*data;
	mlx_color	color;

	data = (t_data *)param;
	color.rgba = 0x000000FF;
	for(int y = 0; y < data->win_infos.height; y++)
		for (int x = 0; x < data->win_infos.width; x++)
			mlx_set_image_pixel(data->mlx, data->frame, x, y, color);
	raycast(data, data->player);
	mlx_put_image_to_window(data->mlx, data->win, data->frame, 0, 0);
}
