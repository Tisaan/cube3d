/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 10:48:33 by pcaplat           #+#    #+#             */
/*   Updated: 2026/05/28 11:44:27 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/raycast.h"
#include "../../includes/utils.h"
#include <math.h>

static void	calc_side_dist_x(t_player *p, t_ray *r, t_vect *tile, t_vect *step)
{
	if (r->dir.x < 0)
	{
		step->x = -1;
		r->side_dist.x = (p->pos.x / WALL_SIZE - tile->x) * r->delta_dist.x;
	}
	else
	{
		step->x = 1;
		r->side_dist.x = (tile->x + 1.0 - p->pos.x / WALL_SIZE);
		r->side_dist.x *= r->delta_dist.x;
	}
}

static void	init_dda(t_ray *r, t_vect *tile, t_vect *step, t_player *p)
{
	t_vect	player_pos;

	set_vect(&player_pos, p->pos.x / WALL_SIZE, p->pos.y / WALL_SIZE);
	tile->x = (int)(p->pos.x / WALL_SIZE);
	tile->y = (int)(p->pos.y / WALL_SIZE);
	if (r->dir.x == 0)
		r->delta_dist.x = INFINITY;
	else
		r->delta_dist.x = ft_abs(1.0 / r->dir.x);
	if (r->dir.y == 0)
		r->delta_dist.y = INFINITY;
	else
		r->delta_dist.y = ft_abs(1.0 / r->dir.y);
	calc_side_dist_x(p, r, tile, step);
	if (r->dir.y < 0)
	{
		step->y = -1;
		r->side_dist.y = (p->pos.y / WALL_SIZE - tile->y) * r->delta_dist.y;
	}
	else
	{
		step->y = 1;
		r->side_dist.y = (tile->y + 1.0 - p->pos.y / WALL_SIZE);
		r->side_dist.y *= r->delta_dist.y;
	}
}

static float	calc_wall_dist(t_ray *ray)
{
	float	dist;

	dist = 0.0;
	if (ray->face == EA || ray->face == WE)
		dist = ray->side_dist.x - ray->delta_dist.x;
	else
		dist = ray->side_dist.y - ray->delta_dist.y;
	if (dist < 0.0001f)
		dist = 0.0001f;
	return (dist);
}

static bool	check_collision(t_data *data, t_vect tile)
{
	if ((int)tile.x >= (int)ft_strlen(data->map->grid[(int)tile.y]))
		return (true);
	if (data->map->grid[(int)tile.y][(int)tile.x] != '0')
		return (true);
	return (false);
}

float	dda(t_ray *ray, t_data *data)
{
	t_vect	tile;
	t_vect	step;
	float	dist;
	bool	is_colliding;

	init_dda(ray, &tile, &step, data->player);
	is_colliding = false;
	ray->side = 0;
	while (is_colliding == false)
	{
		set_ray_side(ray, &tile, step);
		if (tile.y < 0 || tile.y >= data->map->height
			|| tile.x < 0 || tile.x >= data->map->width)
		{
			set_ray_face(ray);
			dist = calc_wall_dist(ray);
			return (dist);
		}
		is_colliding = check_collision(data, tile);
	}
	set_ray_face(ray);
	dist = calc_wall_dist(ray);
	return (dist);
}
