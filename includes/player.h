/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 16:01:24 by pcaplat           #+#    #+#             */
/*   Updated: 2026/05/10 10:58:01 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H
# include "vectors.h"
# include "../mlx/includes/mlx.h"

typedef struct s_data	t_data;

typedef struct	s_player
{
	mlx_image	sprite;
	t_vect		pos;
	t_vect		dir;
	int			size;
	float		aov; // angle of view
	float		fov; //convention : 90deg mais 60deg fine
}				t_player;

int		init_player(t_data *data);

#endif
