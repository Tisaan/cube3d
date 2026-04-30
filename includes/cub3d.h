/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:27:28 by tseche            #+#    #+#             */
/*   Updated: 2026/04/30 21:08:13 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <math.h>

#include "../libft/libft.h"
#include "../gnl/get_next_line.h"
#include "../mlx/includes/mlx.h"

#include "parsing.h"

typedef mlx_window_create_info	t_win_infos;

typedef struct s_vect
{
	float	x;
	float	y;
	float	z;
}				t_vect;

typedef struct s_map
{
	char	**grid;
	t_vect	*player_pos;
	int		width;
	int		height;
	int		*start;// [0] = x, [1] = y, [2] = direction
}				t_map;

typedef struct s_data
{
	mlx_context		mlx;
	mlx_window		win;
	t_win_infos		win_infos;
	t_map			*map;
	t_texture_path	texture[4];
	t_prgb			plans_color[2];
}				t_data;

#endif
