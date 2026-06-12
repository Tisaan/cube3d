/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 17:04:03 by pcaplat           #+#    #+#             */
/*   Updated: 2026/06/12 14:26:09 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/mini_map.h"
#include "../includes/utils.h"

static void	place_remove_player(t_player *player, t_data *d, bool remove)
{
	int	tile_x;
	int	tile_y;

	tile_x = player->pos.x / WALL_SIZE;
	tile_y = player->pos.y / WALL_SIZE;
	if (!remove)
		d->map->grid[tile_y][tile_x] = 'P';
	else if (d->map_door[tile_y][tile_x] != not_door_state)
		d->map->grid[tile_y][tile_x] = 'D';
	else
		d->map->grid[tile_y][tile_x] = '0';
}

void	update_mini_map(void *param)
{
	int		ret;
	t_data	*data;

	data = (t_data *)param;
	place_remove_player(data->player, data, false);
	ret = set_viewport(data->player, data->map);
	if (ret < 0)
		return ;
	set_mini_map_pixels(data);
	free_viewport(data);
	data->map->viewport = NULL;
	place_remove_player(data->player, data, true);
}

static void	render_player_sprite(t_data *data)
{
	t_animated_sprite_2d	*s;

	s = &data->player->sprite;
	mlx_put_image_to_window(data->mlx, data->win, s->spritesheet[0], s->x, s->y);
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
	mlx_put_image_to_window(data->mlx, data->win, data->mini_map,
		win.width - 176 - 10, 10);
	render_player_sprite(data);
}
