/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: von <von@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 17:04:03 by pcaplat           #+#    #+#             */
/*   Updated: 2026/06/03 17:56:47 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/bonus.h"

void	update_mini_map(void *param)
{
	int		x;
	int		y;
	t_data	*data;
	mlx_color	color;

	color.rgba = 0xFFFFFFFF;
	data = (t_data *)param;
	y = 0;
	set_mini_map_pixels(data);
	while (y < MINI_MAP_SIZE)
	{
		x = 0;
		while (x < MINI_MAP_SIZE)
		{
			mlx_set_image_pixel(data->mlx, data->mini_map, x, y, color);
			x++;
		}
		y++;
	}
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
	mlx_put_image_to_window(data->mlx, data->win, data->mini_map, win.width - MINI_MAP_SIZE - 10, 10);
}
