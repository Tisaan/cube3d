/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 10:09:42 by pcaplat           #+#    #+#             */
/*   Updated: 2026/06/15 15:01:55 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_BONUS_H
# define RAYCAST_BONUS_H
# include "cub3d_bonus.h"
# include "parsing_bonus.h"
# include "objs_bonus.h"

typedef enum e_type
{
	door_type,
	wall_type,
}				t_type;

typedef struct s_ray
{
	int				side;
	t_vect			dir;
	t_vect			delta_dist;
	t_vect			side_dist;
	t_direction_id	face;
	t_type			type;
	int				texture_y;
	union
	{
		struct
		{
			t_vect	tile;
			bool	open;
		};
	};
}					t_ray;

// Raycaster main functions
int		raycast(t_data *data, t_player *player);
float	dda(t_ray *ray, t_data *data);

// Ray util functions
void	set_ray_face(t_ray *ray);
void	set_ray_side(t_ray *ray, t_vect *tile, t_vect step);
void	set_type_ray(t_data *data, t_vect tyle, t_ray *ray);
void	get_pixel(t_ray *ray, mlx_color *pixel, t_data *d,
			int xs[2]);
bool	face_same_dir(t_ray *ray, t_player *p);

#endif
