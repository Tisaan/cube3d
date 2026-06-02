/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: von <von@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 17:04:03 by pcaplat           #+#    #+#             */
/*   Updated: 2026/06/01 16:33:56 by von              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	render(void *param)
{
	t_data		*data;
	mlx_color	color;

	data = (t_data *)param;
	color.rgba = 0x000000FF;
	mlx_clear_window(data->mlx, data->win, color);
	mlx_put_image_to_window(data->mlx, data->win, data->frame, 0, 0);
}
