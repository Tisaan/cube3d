/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 16:01:24 by pcaplat           #+#    #+#             */
/*   Updated: 2026/05/06 19:22:29 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H
# include "vectors.h"

typedef struct s_data	t_data;

typedef struct	s_player
{
	t_vect		pos;
	int			size;
	float		aov; // angle of view
	float		fov; //convention : 90deg mais 60deg fine
}				t_player;

int	init_player(t_data *data);

#endif
