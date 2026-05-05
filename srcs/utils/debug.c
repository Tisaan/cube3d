/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 11:04:11 by pcaplat           #+#    #+#             */
/*   Updated: 2026/05/05 12:02:16 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	display_map_data(t_data data)
{
	printf("%d: <%s>\n", data.texture[0].dir, data.texture[0].path);
	printf("%d: <%s>\n", data.texture[1].dir, data.texture[1].path);
	printf("%d: <%s>\n", data.texture[2].dir, data.texture[2].path);
	printf("%d: <%s>\n", data.texture[3].dir, data.texture[3].path);
	printf("Ceiling color: (%d, %d, %d)\tFloor color: (%d, %d, %d)\n", data.plans_color[CEILING - 5].rgb[0],data.plans_color[CEILING - 5].rgb[1],data.plans_color[CEILING - 5].rgb[2],
		data.plans_color[FLOOR - 5].rgb[0],data.plans_color[FLOOR - 5].rgb[1],data.plans_color[FLOOR - 5].rgb[2]);
}

void	ft_print_error(const char *msg)
{
	write(2, msg, ft_strlen(msg));
}

void	init_pip_boy(t_img *img, t_data *data)
{
	img->asset = mlx_new_image_from_file(data->mlx, "assets/pip_boy.png", &img->width, &img->height);
	img->data = data;
}
