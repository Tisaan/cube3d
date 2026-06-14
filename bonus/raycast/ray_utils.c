/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 11:40:09 by pcaplat           #+#    #+#             */
/*   Updated: 2026/06/14 12:18:41 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast.h"
#include "../includes/objs.h"
#include "../includes/bonus.h"

void	set_ray_side(t_ray *ray, t_vect *tile, t_vect step)
{
	if (ray->side_dist.x < ray->side_dist.y)
	{
		ray->side_dist.x += ray->delta_dist.x;
		tile->x += step.x;
		ray->side = 0;
	}
	else
	{
		ray->side_dist.y += ray->delta_dist.y;
		tile->y += step.y;
		ray->side = 1;
	}
}

void	set_ray_face(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir.x > 0)
			ray->face = EA;
		else
			ray->face = WE;
		return ;
	}
	if (ray->dir.y > 0)
		ray->face = SO;
	else
		ray->face = NO;
}

void	set_type_ray(t_data *data, t_vect tyle, t_ray *ray)
{
	if (data->map->doors[(int)tyle.y][(int)tyle.x] != ' ')
	{
		ray->type = door_type;
		ray->tile = tyle;
	}
	else if (data->map->grid[(int)tyle.y][(int)tyle.x] == '1')
		ray->type = wall_type;
}

void	udpate_doors(t_ray *ray, t_data *d)
{
	// if (ray->type == door_type)
	// {
	// 	if (d->map_door[(int)ray->tile.y][(int)ray->tile.x] == close_state
	// 		&& d->keys.e && ray->delta_dist.x <= 2.0f
	// 		&& ray->delta_dist.y <= 2.0f && face_same_dir(ray, d->player))
	// 	{
	// 		d->map_door[(int)ray->tile.y][(int)ray->tile.x] = open_state;
	// 		d->keys.e = false;
	// 	}
	// 	else if (
	// 		d->map_door[(int)d->player->pos.y / WALL_SIZE]
	// 		[(int)d->player->pos.x / WALL_SIZE] == not_door_state
	// 		&& d->map_door[(int)ray->tile.y][(int)ray->tile.x] == open_state
	// 		&& d->keys.e && ray->delta_dist.x <= 2.0f
	// 		&& ray->delta_dist.y <= 2.0f && face_same_dir(ray, d->player))
	// 	{
	// 		d->map_door[(int)ray->tile.y][(int)ray->tile.x] = close_state;
	// 		d->keys.e = false;
	// 	}
	// }
	
	if (ray->type == door_type)
	{
		if (d->keys.e)
		{
			printf("e enable!\n");
			if (d->map->doors[(int)ray->tile.y][(int)ray->tile.x] == '1')
				d->map->doors[(int)ray->tile.y][(int)ray->tile.x] = '0';
			else
				d->map->doors[(int)ray->tile.y][(int)ray->tile.x] = '1';
			d->keys.e = false;
		}
	}
}

void	get_pixel(t_ray *ray, mlx_color *pixel, t_data *d, int xs[2])
{
	udpate_doors(ray, d);
	if (ray->type == wall_type)
		*pixel = mlx_get_image_pixel(d->mlx, d->wall_assets[ray->face],
				xs[1], ray->texture_y);
	else if (d->map->doors[(int)ray->tile.y][(int)ray->tile.x] == '1')
		*pixel = mlx_get_image_pixel(d->mlx, d->door_asset[0],
				xs[1], ray->texture_y);
	// else
	// 	*pixel = mlx_get_image_pixel(d->mlx, d->door_asset[1],
	// 			xs[1], ray->texture_y);
}
