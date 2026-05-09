/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 17:04:03 by pcaplat           #+#    #+#             */
/*   Updated: 2026/05/09 17:37:46 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	render_player(void *param)
{
	t_player	*player;
	t_data		*data;
	int			px;
	int			py;

	data = (t_data *)param;
	player = data->player;
	px = (int)player->pos.x * WALL_SIZE;
	py = (int)player->pos.y * WALL_SIZE;
	printf("player pos: (%d, %d)\n", px, py);
	mlx_put_image_to_window(data->mlx, data->win, player->sprite, py, px);
}

int	render_2D_map(t_data *data)
{
	t_map		*map;
	int			x;
	int			y;
	
	map = data->map;
	y = 0;
	while (map->grid[y])
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (map->grid[y][x] == '1')
				mlx_put_image_to_window(data->mlx, data->win, data->wall_assets[0], x * WALL_SIZE, y * WALL_SIZE);
			x++;
		}
		y++;
	}
	return (NO_ERROR);
}
