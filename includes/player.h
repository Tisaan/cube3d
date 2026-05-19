/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 16:01:24 by pcaplat           #+#    #+#             */
/*   Updated: 2026/05/19 12:16:34 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H
# ifndef PLAYER_SPEED
#  define PLAYER_SPEED	200.0f
# endif
# ifndef PLAYER_RADIUS
#  define PLAYER_RADIUS 16
# endif

#include "parsing.h"
# include "vectors.h"
# include "../mlx/includes/mlx.h"

typedef struct s_data	t_data;

typedef struct	s_player
{
	mlx_image	sprite;
	t_vect		camera;
	t_vect		pos;
	t_vect		dir;
	t_vect		dest;
	int			size;
}				t_player;

int		init_player(t_data *data);
void	update_player_pos(void *param);

#endif
