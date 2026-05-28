/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 10:09:42 by pcaplat           #+#    #+#             */
/*   Updated: 2026/05/28 11:43:39 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	RAYCAST_H
# define RAYCAST_H
# include "cub3d.h"
#include "parsing.h"

typedef struct	s_ray
{
	int				side;
	t_vect			dir;
	t_vect			delta_dist;
	t_vect			side_dist;
	t_direction_id	face;
}					t_ray;

int	raycast(t_data *data, t_player *player);

// Ray Utils 
void	set_ray_face(t_ray *ray);
void	set_ray_side(t_ray *ray, t_vect *tile, t_vect step);

#endif
