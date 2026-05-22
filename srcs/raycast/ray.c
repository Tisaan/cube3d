/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 10:00:26 by pcaplat           #+#    #+#             */
/*   Updated: 2026/05/22 16:46:39 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/raycast.h"

float	dda(t_ray *ray, t_data *data);

// static mlx_color	get_wall_color(t_direction_id face)
// {
// 	mlx_color	color;
//
// 	if (face == NO)
// 		color.rgba = 0x05003dFF; // dark blue
// 	else if (face == SO)
// 		color.rgba = 0x400205FF; // dark red
// 	else if (face == WE)
// 		color.rgba = 0x230042FF; // dark purple
// 	else
// 		color.rgba = 0x042601FF; // dark green
// 	return (color);
// }

static void	draw_col(t_data *data, float wall_dist, int x, t_ray *ray)
{
	int			wall_height;
	int	 	   start_end[2];
	int	 	   asset_pos[3];
	float		curr_pos;
	float		wall_x;
	float		step;
	mlx_color	pixel;

	wall_height = (int)(data->win_infos.height / wall_dist);
	start_end[0] = -wall_height / 2 + data->win_infos.height / 2;
	start_end[1] = wall_height / 2 +  data->win_infos.height / 2;
	if (ray->face == EA || ray->face == WE)
		wall_x = data->player->pos.y / WALL_SIZE + wall_dist * ray->dir.y;
	else
		wall_x = data->player->pos.x / WALL_SIZE + wall_dist * ray->dir.x;
	wall_x -= floorf(wall_x);
	asset_pos[0] = (int)(wall_x * WALL_SIZE);
	if (asset_pos[0] < 0)
		asset_pos[0] = 0;
	if (asset_pos[0] >= WALL_SIZE)
		asset_pos[0] = WALL_SIZE - 1;
	if ((ray->face == EA && ray->dir.x > 0)
    || (ray->face == WE && ray->dir.x < 0)
    || (ray->face == NO && ray->dir.y < 0)
    || (ray->face == SO && ray->dir.y > 0))
		asset_pos[0] = WALL_SIZE - asset_pos[0] - 1;
	step = (float)WALL_SIZE / wall_height;
	curr_pos = (start_end[0] - data->win_infos.height / 2 + wall_height / 2) * step;
	if (start_end[0] < 0)
	{
		curr_pos = -start_end[0] * step;
		start_end[0] = 0;
	}
	if (start_end[1] > data->win_infos.height)
		start_end[1] = data->win_infos.height;
	int y = 0;
	while (y < start_end[0])
	{
		mlx_set_image_pixel(data->mlx, data->frame, x, y, data->ceil_color);
		y++;
	}
	while (y < start_end[1])
	{
		asset_pos[1] = (int)curr_pos;
		if (asset_pos[1] < 0)
			asset_pos[1] = 0;
		if (asset_pos[1] >= WALL_SIZE)
			asset_pos[1] = WALL_SIZE - 1;
		pixel = mlx_get_image_pixel(data->mlx, data->wall_assets[ray->face], asset_pos[0], asset_pos[1]);
		mlx_set_image_pixel(data->mlx, data->frame, x, y, pixel);
		curr_pos += step;
		y++;
	}
	while (y < data->win_infos.height)
	{
		mlx_set_image_pixel(data->mlx, data->frame, x, y, data->floor_color);
		y++;
	}
}

// static void	draw_3D(t_data *data, float wall_dist, int x, t_direction_id ray_face)
// {
// 	mlx_color	wall_color;
// 	mlx_color	ceil_color;
// 	mlx_color	floor_color;
// 	int			wall_height;
// 	int			start;
// 	int			end;
// 	int			y;
//
// 	if (wall_dist < 0.00001f)
// 		wall_dist = 0.00001f;
// 	wall_height = (int)(data->win_infos.height / wall_dist);
// 	start = -wall_height / 2 + data->win_infos.height / 2;
// 	if (start < 0)
// 		start = 0;
// 	end = wall_height / 2 +  data->win_infos.height / 2;
// 	if (end >= data->win_infos.height)
// 		end = data->win_infos.height - 1;
//
// 	wall_color = get_wall_color(ray_face);
// 	ceil_color.rgba = 0x87CEEBFF;
// 	floor_color.rgba = 0x141414FF;
//
// 	y = 0;
// 	while (y < start)
// 	{
// 		mlx_set_image_pixel(data->mlx, data->frame, x, y, ceil_color);
// 		y++;
// 	}
// 	while (y < end)
// 	{
// 		mlx_set_image_pixel(data->mlx, data->frame, x, y, wall_color);
// 		y++;
// 	}
// 	while (y < data->win_infos.height)
// 	{
// 		mlx_set_image_pixel(data->mlx, data->frame, x, y, floor_color);
// 		y++;
// 	}
// }

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
		// printf("%f\n", wall_dist);
		draw_col(data, wall_dist, x, &ray);
		x++;
	}
	return (NO_ERROR);
}
