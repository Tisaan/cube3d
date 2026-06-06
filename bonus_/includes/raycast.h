/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 10:09:42 by pcaplat           #+#    #+#             */
/*   Updated: 2026/06/06 15:19:51 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	RAYCAST_H
# define RAYCAST_H
# include "cub3d.h"
#include "parsing.h"
#include "objs.h"

typedef enum	e_type
{
	door_type,
	wall_type,
}				t_type;

typedef struct	s_ray
{
	int				side;
	t_vect			dir;
	t_vect			delta_dist;
	t_vect			side_dist;
	t_direction_id	face;
	t_type   		type;
	union {
		t_vect	tile;
	};
}					t_ray;

// Raycaster main functions
int	raycast(t_data *data, t_player *player);
float	dda(t_ray *ray, t_data *data);

// Ray util functions
void	set_ray_face(t_ray *ray);
void	set_ray_side(t_ray *ray, t_vect *tile, t_vect step);
void	set_type_ray(t_data *data, t_vect tyle, t_ray *ray);
void	get_pixel(t_ray *ray, mlx_color *pixel, t_data *d, int xs[2], int texture_y);
bool	face_same_dir(t_ray *ray, t_player *p);

#endif
