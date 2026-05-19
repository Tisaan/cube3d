/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 16:01:24 by pcaplat           #+#    #+#             */
/*   Updated: 2026/05/19 11:27:31 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H
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
	int			size;
	float		speed;
	float		rot_speed;
}				t_player;

int		init_player(t_data *data);
void	update_player_pos(void *param);

#endif
