/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 17:04:03 by pcaplat           #+#    #+#             */
/*   Updated: 2026/05/12 14:26:11 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/raycast.h"

// static void	render_player(t_data *data)
// {
// 	t_player	*player;
// 	int			px;
// 	int			py;
//
// 	player = data->player;
// 	px = (int)player->pos.x;
// 	py = (int)player->pos.y;
// 	mlx_put_image_to_window(data->mlx, data->win, player->sprite, px, py);
// }

static void	render_2D_map(t_data *data)
{
	// t_map		*map;
	// // int			x;
	// int			y;
	//
	// map = data->map;
	raycast(data, data->player);
	// y = 0;
	// while (map->grid[y])
	// {
	// 	x = 0;
	// 	while (map->grid[y][x])
	// 	{
	// 		if (map->grid[y][x] == '1')
	// 			mlx_put_image_to_window(data->mlx, data->win, data->wall_assets[0], x * WALL_SIZE, y * WALL_SIZE);
	// 		else
	// 			mlx_put_image_to_window(data->mlx, data->win, data->floor_asset, x * WALL_SIZE, y * WALL_SIZE);
	// 		x++;
	// 	}
	// 	y++;
	// }
}

void	render(void *param)
{
	t_data		*data;
	mlx_color	bg;

	data = (t_data *)param;
	bg.r = 0;
	bg.g = 0;
	bg.b = 0;
	bg.a = 100;
	mlx_clear_window(data->mlx, data->win, bg);
	render_2D_map(data);
	// render_player(data);
}


