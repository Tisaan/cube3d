/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: von <von@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:27:28 by tseche            #+#    #+#             */
/*   Updated: 2026/06/01 16:36:36 by von              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H
# ifndef WALL_SIZE
#  define WALL_SIZE 64
# endif

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <math.h>

#include "../../libft/libft.h"
#include "../../gnl/get_next_line.h"
#include "../../mlx/includes/mlx.h"
#include "../../mlx/includes/mlx_extended.h"

#include "parsing.h"
#include "player.h"
#include "utils.h"

typedef mlx_window_create_info	t_win_infos;

typedef enum	e_key_code
{
	Q_KEY = 20,
	ESC_KEY = 41,
	F_KEY = 9,
	W_KEY = 26,
	A_KEY = 4,
	S_KEY = 22,
	D_KEY = 7,
	UP = 82,
	LEFT = 80,
	DOWN = 81,
	RIGHT = 79
}	t_key_code;

typedef enum	e_win_event
{
	WIN_CLOSE = 0,
	WIN_RESIZE = 8,
}	t_win_event;

typedef struct	s_keys
{
	bool	w;
	bool	a;
	bool	s;
	bool	d;
	bool	left;
	bool	right;
}			t_keys;

typedef struct s_data
{
	mlx_context		mlx;
	mlx_window		win;
	mlx_image		wall_assets[4];
	mlx_image		frame;
	mlx_color		ceil_color;
	mlx_color		floor_color;
	t_timer			timer;
	t_win_infos		win_infos;
	t_map			*map;
	t_texture_path	texture[4];
	t_prgb			plans_color[2];
	t_player		*player;
	t_keys			keys;
	float			delta;
}				t_data;

typedef struct	s_img
{
	mlx_image	asset;
	char		*path;
	int			width;
	int			height;
}				t_img;

// Hooks
void	key_hooks(int key, void *param);
void	key_up_hook(int key, void *param);
void	window_hook(int event, void *param);
void	render(void *param);
void	ray_hook(void *param);


#endif
