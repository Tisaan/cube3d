/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: von <von@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 17:04:03 by pcaplat           #+#    #+#             */
/*   Updated: 2026/06/05 18:34:23 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/mini_map.h"

static void	place_remove_player(t_player *player, t_map *map, bool remove)
{
	// static bool	display = true;
	int	tile_x;
	int	tile_y;

	tile_x = player->pos.x / WALL_SIZE;
	tile_y = player->pos.y / WALL_SIZE;
	if (!remove)
		map->grid[tile_y][tile_x] = 'P';
	else
		map->grid[tile_y][tile_x] = '0';
}

void	update_mini_map(void *param)
{
	// int		x;
	// int		y;
	int		ret;
	t_data	*data;
	mlx_color	color;

	color.rgba = 0xFFFFFFFF;
	data = (t_data *)param;
	place_remove_player(data->player, data->map, false);
	ret = set_viewport(data->player, data->map);
	if (ret < 0)
		return ;
	system("clear");
	for (int i = 0; i < 11; i++)
		printf("%d, <%s>\n", i, data->map->viewport[i]);
	set_mini_map_pixels(data);
	for (int i = 0; i <= 11; i++)
		free(data->map->viewport[i]);
	free(data->map->viewport);
	data->map->viewport = NULL;
	place_remove_player(data->player, data->map, true);
	// y = 0;
	// while (y < MINI_MAP_SIZE)
	// {
	// 	x = 0;
	// 	while (x < MINI_MAP_SIZE)
	// 	{
	// 		mlx_set_image_pixel(data->mlx, data->mini_map, x, y, color);
	// 		x++;
	// 	}
	// 	y++;
	// }
}

void	render(void *param)
{
	t_data		*data;
	mlx_color	color;
	t_win_infos	win;

	data = (t_data *)param;
	win = data->win_infos;
	color.rgba = 0x000000FF;
	mlx_clear_window(data->mlx, data->win, color);
	mlx_put_image_to_window(data->mlx, data->win, data->frame, 0, 0);
	mlx_put_image_to_window(data->mlx, data->win, data->mini_map, win.width - 176 - 10, 10);
}
