/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 10:00:26 by pcaplat           #+#    #+#             */
/*   Updated: 2026/05/12 16:16:51 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/raycast.h"

float	dda(t_ray *ray, t_data *data);

static void	draw_3D(t_data *data, float wall_dist, int x)
{
	mlx_color	color;
	int			wall_height;
	int			start;
	int			end;
	// float		fov;

	// fov = 1.0f / tan(33.0f * M_PI / 180.0f);
	wall_height = (int)(data->win_infos.height / wall_dist);

	start = -wall_height / 2 + data->win_infos.height / 2;
	if (start < 0)
		start = 0;
	end = wall_height / 2 +  data->win_infos.height / 2;
	if (end >= data->win_infos.height)
		end = data->win_infos.height - 1;
	color.rgba = 0xFFFFFFFF;
	while (start < end)
	{
		mlx_pixel_put(data->mlx, data->win, x, start, color);
		start++;
	}
}

int	raycast(t_data *data, t_player *player)
{
	t_ray		ray;
	int			x;
	float		camera_x;
	float		wall_dist;

	camera_x = 0;
	x = 0;
	while (x < data->win_infos.width)
	{
		camera_x = 2 * x / (float)(data->win_infos.width) - 1;
		// printf("c_x : %f\n", camera_x);
		ray.dir.x= player->dir.x + player->camera.x * camera_x;
		ray.dir.y = player->dir.y + player->camera.y * camera_x;
		// printf("ray (%f, %f)\n", ray.dir.x, ray.dir.y);
		wall_dist = dda(&ray, data);
		printf("%f\n", wall_dist);
		draw_3D(data, wall_dist, x);
		x++;
	}
	return (NO_ERROR);
}
