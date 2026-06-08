/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 15:13:28 by tseche            #+#    #+#             */
/*   Updated: 2026/06/08 16:47:24 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/raycast.h"

static bool	between(float n)
{
	if (n > 0.5f)
		return (false);
	else if (n < -0.5f)
		return (false);
	return (true);
}

bool	face_same_dir(t_ray *ray, t_player *p)
{
	if (ray->face == NO && p->dir.y <= 0.0f && between(p->dir.x))
		return (true);
	else if (ray->face == SO && p->dir.y >= 0.0f && between(p->dir.x))
		return (true);
	if (ray->face == WE && p->dir.x <= 0.0f && between(p->dir.y))
		return (true);
	else if (ray->face == EA && p->dir.x >= 0.0f && between(p->dir.y))
		return (true);
	return (false);
}