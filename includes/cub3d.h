/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:27:28 by tseche            #+#    #+#             */
/*   Updated: 2026/05/04 18:56:23 by tseche           ###   ########.fr       */
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
#include "../mlx/includes/mlx_extended.h"

#include "parsing.h"

typedef mlx_window_create_info	t_win_infos;

typedef enum	e_key_code
{
	Q_KEY = 20,
	ESC_KEY = 41,
	F_KEY = 9,
}	t_key_code;

typedef enum	e_win_event
{
	WIN_CLOSE = 0,
	WIN_RESIZE = 8,
}	t_win_event;

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

typedef struct	s_img
{
	mlx_image	asset;
	t_data		*data;
	char		*path;
	int			width;
	int			height;
}				t_img;

#endif
