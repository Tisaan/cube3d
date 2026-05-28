/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 10:48:33 by pcaplat           #+#    #+#             */
/*   Updated: 2026/05/21 14:33:26 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/raycast.h"
#include "../../includes/utils.h"
#include <math.h>

static float	calc_side_dist_x(t_data *data, t_ray *ray, t_vect *step)
{
	return (0.0);
}

static void	init_dda(t_ray *ray, t_vect *tile, t_vect *step, t_data *data)
{
	t_vect	player_pos;

	set_vect(&player_pos, data->player->pos.x / WALL_SIZE, data->player->pos.y / WALL_SIZE);
	tile->x = (int)(data->player->pos.x / WALL_SIZE);
	tile->y = (int)(data->player->pos.y / WALL_SIZE);
	if (ray->dir.x == 0)
		ray->delta_dist.x = INFINITY;
	else
		ray->delta_dist.x = ft_abs(1.0 / ray->dir.x);
	if (ray->dir.y == 0)
		ray->delta_dist.y = INFINITY;
	else
		ray->delta_dist.y = ft_abs(1.0 / ray->dir.y);
	if (ray->dir.x < 0)
	{
		step->x = -1;
		ray->side_dist.x = (data->player->pos.x / WALL_SIZE - tile->x) * ray->delta_dist.x;
	}
	else
	{
		step->x = 1;
		ray->side_dist.x = (tile->x + 1.0 - data->player->pos.x / WALL_SIZE) * ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		step->y = -1;
		ray->side_dist.y = (data->player->pos.y / WALL_SIZE - tile->y) * ray->delta_dist.y;
	}
	else
	{
		step->y = 1;
		ray->side_dist.y = (tile->y + 1.0 - data->player->pos.y / WALL_SIZE) * ray->delta_dist.y;
	}
}

float	dda(t_ray *ray, t_data *data)
{
	t_vect	tile;
	t_vect	step;
	int		side;
	float	dist;
	bool	is_colliding;

	init_dda(ray, &tile, &step, data);
	// printf("tile (%f, %f), step(%f, %f)\n", tile.x, tile.y, step.x, step.y);
	is_colliding = false;
	side = 0;
	while (is_colliding == false)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			tile.x += step.x;
			side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			tile.y += step.y;
			side = 1;
		}
		if (tile.y < 0 || tile.y >= data->map->height
			|| tile.x < 0 || tile.x >= data->map->width)
		{
			 if (side == 0)
			{
				if (ray->dir.x > 0)
					ray->face = EA;
				else
					ray->face = WE;
				dist = ray->side_dist.x - ray->delta_dist.x;
				if (dist < 0.0001f)
					dist = 0.0001f;
				return (dist);
			}
			if (ray->dir.y > 0)
				ray->face = SO;
			else
				ray->face = NO;
			dist = ray->side_dist.y - ray->delta_dist.y;
			if (dist < 0.0001f)
				dist = 0.0001f;
			return (dist);
		}
		if ((int)tile.x >= (int)ft_strlen(data->map->grid[(int)tile.y]))
		{
			is_colliding = true;
			break ;
		}
		if (data->map->grid[(int)tile.y][(int)tile.x] != '0')
			is_colliding = true;
	}
	if (side == 0)
	{
		if (ray->dir.x > 0)
			ray->face = WE;
		else
			ray->face = EA;
		return (ray->side_dist.x - ray->delta_dist.x);
	}
	if (ray->dir.y > 0)
		ray->face = NO;
	else
		ray->face = SO;
	return (ray->side_dist.y - ray->delta_dist.y);
}
