/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:27:28 by tseche            #+#    #+#             */
/*   Updated: 2026/04/29 10:39:18 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <math.h>

#include "../libft/libft.h"
#include "../gnl/get_next_line.h"
#include "../mlx/includes/mlx.h"

#include "parsing.h"

typedef struct s_win
{
	//image
	//win
	//
}				t_win;

typedef struct s_vect
{
	float	x;
	float	y;
	float	z;
}				t_vect;

typedef struct s_map
{
	char	**map;
	t_vect	*player_pos;
}				t_map;

typedef struct s_data
{
	t_map			*map;
	t_win 			*windows;
	t_texture_path 	texture[4];
	t_pceilfloor	floorceil[2];
	
}				t_data;

#endif
