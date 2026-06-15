/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: von <von@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:27:28 by tseche            #+#    #+#             */
/*   Updated: 2026/06/15 13:50:21 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H
# ifndef WALL_SIZE
#  define WALL_SIZE 64
# endif
# ifndef FONT_SIZE
#  define FONT_SIZE 20
# endif

# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/time.h>
# include <math.h>

# include "../../libft/libft.h"
# include "../../gnl/get_next_line.h"
# include "../../mlx/includes/mlx.h"
# include "../../mlx/includes/mlx_extended.h"

# include "parsing_bonus.h"
# include "player_bonus.h"
# include "utils_bonus.h"

# define WIN_HEIGHT 720
# define WIN_WIDTH 1280

# define DOOR_ASSET_CLOSE "assets/wood.png"
# define DOOR_ASSET_OPEN "assets/pillar.png"

typedef mlx_window_create_info	t_win_infos;

typedef enum e_key_code
{
	Q_KEY = 20,
	ESC_KEY = 41,
	F_KEY = 9,
	W_KEY = 26,
	A_KEY = 4,
	S_KEY = 22,
	D_KEY = 7,
	E_KEY = 8,
	UP = 82,
	LEFT = 80,
	DOWN = 81,
	RIGHT = 79,
	F3_KEY = 60
}	t_key_code;

typedef enum e_win_event
{
	WIN_CLOSE = 0,
	WIN_RESIZE = 8,
}	t_win_event;

typedef struct s_keys
{
	bool	w;
	bool	a;
	bool	s;
	bool	d;
	bool	e;
	bool	e_lock;
	bool	f;
	bool	left;
	bool	right;
	bool	f3;
}			t_keys;

typedef enum e_state_obj
{
	close_state,
	open_state,
	not_door_state,
}				t_state_obj;

typedef struct s_data
{
	mlx_context		mlx;
	mlx_window		win;
	mlx_image		wall_assets[4];
	mlx_image		frame;
	mlx_image		door_asset[2];
	mlx_image		mini_map;
	mlx_color		ceil_color;
	mlx_color		floor_color;
	t_timer			timer;
	t_win_infos		win_infos;
	t_map			*map;
	t_state_obj		**map_door;
	t_texture_path	texture[4];
	t_prgb			plans_color[2];
	t_player		*player;
	t_keys			keys;
	t_vect			*mouse_pos;			
	char			*seed;
	float			delta;
}				t_data;

typedef struct s_img
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
void	update_mini_map(void *param);
void	update_mouse_rot(t_data *d);
void	ray_hook(void *param);
void	handle_mouse_clic(int event, void *param);
char	**set_doors_map(t_data *data);

#endif
