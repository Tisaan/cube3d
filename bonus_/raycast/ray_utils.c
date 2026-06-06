/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 11:40:09 by pcaplat           #+#    #+#             */
/*   Updated: 2026/06/06 15:20:25 by tseche           ###   ########.fr       */
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
	if (data->map->grid[(int)tyle.y][(int)tyle.x] == 'D')
	{
		ray->type = door_type;
		ray->tile = tyle;
	}
	else
		ray->type = wall_type;
}

void	udpate_doors(t_ray *ray, t_data *d)
{
	if (ray->type == door_type)
	{
		// if ((d->map_door[(int)ray->tile.y][(int)ray->tile.x] == close_state || d->map_door[(int)ray->tile.y][(int)ray->tile.x] == open_state) && d->keys.e)
		// {
		// 	printf("dist[%f, %f]\n", ray->delta_dist.x, ray->delta_dist.y);
		// }
		if (d->map_door[(int)ray->tile.y][(int)ray->tile.x] == close_state && d->keys.e
		&& ray->delta_dist.x <= 2.0f && ray->delta_dist.y <= 2.0f
	&& face_same_dir(ray, d->player))
		{
			d->map_door[(int)ray->tile.y][(int)ray->tile.x] = open_state;
			d->keys.e = false;
		}
		else if (d->map_door[(int)ray->tile.y][(int)ray->tile.x] == open_state && d->keys.e
		&& ray->delta_dist.x <= 2.0f && ray->delta_dist.y <= 2.0f
	&& face_same_dir(ray, d->player))
		{
			d->map_door[(int)ray->tile.y][(int)ray->tile.x] = close_state;
			d->keys.e = false;
		}
	}
}

void	get_pixel(t_ray *ray, mlx_color *pixel, t_data *d, int xs[2], int texture_y)
{
	udpate_doors(ray, d);
	if (ray->type == wall_type)
		*pixel = mlx_get_image_pixel(d->mlx, d->wall_assets[ray->face],
					xs[1], texture_y);
	else if (d->map_door[(int)ray->tile.y][(int)ray->tile.x] == close_state || d->map_door[(int)ray->tile.y][(int)ray->tile.x] == closing_state)
		*pixel = mlx_get_image_pixel(d->mlx, d->door_asset[0],
					xs[1], texture_y);
	else
		*pixel = mlx_get_image_pixel(d->mlx, d->door_asset[1],
					xs[1], texture_y);
}
