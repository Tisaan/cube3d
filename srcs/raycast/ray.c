/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 10:00:26 by pcaplat           #+#    #+#             */
/*   Updated: 2026/06/05 14:43:05 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/raycast.h"
#include "../includes/objs.h"

static int	get_texture_x(t_player *p, t_ray *ray, float wall_dist)
{
	float	obj_x;
	int		texture_x;

	if (ray->face == EA || ray->face == WE)
		obj_x = p->pos.y / WALL_SIZE + wall_dist * ray->dir.y;
	else
		obj_x = p->pos.x / WALL_SIZE + wall_dist * ray->dir.x;
	obj_x -= floorf(obj_x);
	texture_x = (int)(obj_x * WALL_SIZE);
	texture_x = clamp_pos(texture_x, 0, WALL_SIZE - 1);
	if ((ray->face == EA && ray->dir.x > 0)
		|| (ray->face == WE && ray->dir.x < 0)
		|| (ray->face == NO && ray->dir.y < 0)
		|| (ray->face == SO && ray->dir.y > 0))
		texture_x = WALL_SIZE - texture_x - 1;
	return (texture_x);
}

static void	set_obj_pixels(t_data *d, t_ray *ray, t_obj obj, int xs[2])
{
	float		curr_pos;
	float		step;
	mlx_color	pixel;
	int			texture_y;
	int			y;

	step = (float)WALL_SIZE / obj.height;
	curr_pos = obj.cliping * step;
	y = obj.start;
	while (y < obj.end)
	{
		texture_y = clamp_pos((int)curr_pos, 0, WALL_SIZE - 1);
		pixel = mlx_get_image_pixel(d->mlx, d->wall_assets[ray->face],
				xs[1], texture_y);
		mlx_set_image_pixel(d->mlx, d->frame, xs[0], y++, pixel);
		curr_pos += step;
	}
}

static void	set_col_pixels(t_data *data, t_ray *ray, int x, float wall_dist)
{
	t_obj	obj;
	int		texture_x;
	int		y;
	int		xs[2];

	obj = get_obj(&data->win_infos, wall_dist);
	texture_x = get_texture_x(data->player, ray, wall_dist);
	y = 0;
	while (y < obj.start)
		mlx_set_image_pixel(data->mlx, data->frame, x, y++, data->ceil_color);
	xs[0] = x;
	xs[1] = texture_x;
	set_obj_pixels(data, ray, obj, xs);
	y = obj.end;
	while (y < data->win_infos.height)
		mlx_set_image_pixel(data->mlx, data->frame, x, y++, data->floor_color);
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
		ray.dir.x = player->dir.x + player->camera.x * camera_x;
		ray.dir.y = player->dir.y + player->camera.y * camera_x;
		wall_dist = dda(&ray, data);
		set_col_pixels(data, &ray, x, wall_dist);
		x++;
	}
	return (NO_ERROR);
}
