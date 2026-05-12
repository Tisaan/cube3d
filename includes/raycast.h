/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 10:09:42 by pcaplat           #+#    #+#             */
/*   Updated: 2026/05/12 11:59:41 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	RAYCAST_H
# define RAYCAST_H
# include "cub3d.h"

typedef struct	s_ray
{
	t_vect	dir;
	t_vect	delta_dist;
	t_vect	side_dist;
}			t_ray;

int	raycast(t_data *data, t_player *player);

#endif
