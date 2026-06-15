/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: von <von@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 16:01:24 by pcaplat           #+#    #+#             */
/*   Updated: 2026/06/15 13:53:01 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_BONUS_H
# define PLAYER_BONUS_H
# ifndef PLAYER_SPEED
#  define PLAYER_SPEED	200.0f
# endif
# ifndef PLAYER_RADIUS
#  define PLAYER_RADIUS	16
# endif
# ifndef PLAYER_ROT_SPEED
#  define PLAYER_ROT_SPEED	3.0f
# endif
# ifndef SPRITE_NAME
#  define SPRITE_NAME	"Shotgun"
# endif
# ifndef SPRITE_PATH
#  define SPRITE_PATH	"assets/sprite/"
# endif
# ifndef SPRITE_FRAMES
#  define SPRITE_FRAMES	7
# endif
# ifndef SPRITE_RATIO
#  define SPRITE_RATIO	0.40f
# endif
# ifndef ANIM_SPEED
#  define ANIM_SPEED	0.1f
# endif

# include "parsing_bonus.h"
# include "vectors_bonus.h"
# include "utils_bonus.h"
# include "../../mlx/includes/mlx.h"

typedef struct s_data	t_data;

typedef struct s_animated_sprite_2d
{
	mlx_image	*spritesheet;
	t_timer		anim_timer;
	int			width;
	int			height;
	int			x;
	int			y;
	int			frame;
	float		scale;
	float		anim_time;
	bool		is_playing;
}				t_animated_sprite_2d;

typedef struct s_player
{
	t_animated_sprite_2d	sprite;
	t_vect					camera;
	t_vect					pos;
	t_vect					dir;
	t_vect					dest;
	int						size;
	bool					can_shoot;
}							t_player;

int		init_player(t_data *data);
int		init_player_sprite(t_data *data);
void	update_player_pos(void *param);
void	update_player_rot(void *param);
void	update_sprite_frame(t_data *data);
void	start_shoot_animation(t_data *data);
void	set_sprite_pos(t_win_infos win, t_animated_sprite_2d *sprite);
void	set_sprite_scale(t_win_infos win, t_animated_sprite_2d *sprite);

#endif
