/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mini_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 18:11:52 by pcaplat           #+#    #+#             */
/*   Updated: 2026/06/10 07:44:36 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	fill_pixels(t_data *data, int x, int y, mlx_color color)
{
	// char		**view;
	int			i;
	int			j;
	// int			count;

	// view = data->map->viewport;
	i = y * 16;
	// count = 0;
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
			else
				color.rgba = 0x000000FF;
			fill_pixels(data, x, y, color);
			x++;
		}
		y++;
	}
}
