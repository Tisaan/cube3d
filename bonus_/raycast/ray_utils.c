/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: von <von@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 11:40:09 by pcaplat           #+#    #+#             */
/*   Updated: 2026/06/01 16:33:48 by von              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast.h"

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
