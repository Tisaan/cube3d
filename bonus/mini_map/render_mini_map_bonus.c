/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mini_map_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 18:11:52 by pcaplat           #+#    #+#             */
/*   Updated: 2026/06/15 14:46:24 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static void	fill_pixels(t_data *data, int x, int y, mlx_color color)
{
	int			i;
	int			j;

	i = y * 16;
	while (i < (y * 16) + 16)
	{
		j = x * 16;
		while (j < (x * 16) + 16)
		{
			mlx_set_image_pixel(data->mlx, data->mini_map, j, i, color);
			j++;
		}
		i++;
	}
}

void	set_mini_map_pixels(t_data *data)
{
	int			y;
	int			x;
	mlx_color	color;

	y = 0;
	while (data->map->viewport[y])
	{
		x = 0;
		while (data->map->viewport[y][x])
		{
			if (data->map->viewport[y][x] == '1')
				color.rgba = 0x595959FF;
			else if (data->map->viewport[y][x] == '0')
				color.rgba = 0x1c1c1cFF;
			else if (data->map->viewport[y][x] == 'P')
				color.rgba = 0x00b7faFF;
			else if (data->map->viewport[y][x] == 'D')
				color.rgba = 0x5c3619FF;
			else
				color.rgba = 0x000000FF;
			fill_pixels(data, x, y, color);
			x++;
		}
		y++;
	}
}

void	toogle_door_state(void *param)
{
	t_data	*data;
	int		px;
	int		py;

	data = (t_data *)param;
	px = (int)(data->player->pos.x / WALL_SIZE + data->player->dir.x);
	py = (int)(data->player->pos.y / WALL_SIZE + data->player->dir.y);
	if (py < 0 || py >= data->map->height || px < 0 || px >= data->map->width)
		return ;
	if (data->keys.e && !data->keys.e_lock)
	{
		if (data->map->doors[py][px] == ' ')
			return ;
		else if (data->map->doors[py][px] == '1')
			data->map->doors[py][px] = '0';
		else
		{
			data->player->pos.x -= data->player->dir.x * WALL_SIZE * 0.1f;
			data->player->pos.y -= data->player->dir.y * WALL_SIZE * 0.1f;
			data->map->doors[py][px] = '1';
		}
		data->keys.e_lock = true;
	}
}
