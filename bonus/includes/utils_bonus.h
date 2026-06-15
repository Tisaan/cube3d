/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 11:25:47 by pcaplat           #+#    #+#             */
/*   Updated: 2026/06/15 14:22:51 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_BONUS_H
# define UTILS_BONUS_H
# include <sys/time.h>
# include "parsing_bonus.h"

typedef struct s_timer
{
	struct timeval	current_time;
	struct timeval	start_time;
	float			fps;
}					t_timer;

void		free_all(t_data *data, int fd);
void		free_texture_paths(t_data *data);
void		free_map(t_data *data);
void		destroy_sprite_assets(t_data *data);
void		clear_gnl_buffer(int fd);
void		clean_exit(t_data *data, bool img_destroy);
float		ft_abs(float nb);
mlx_color	rgb_to_color(t_prgb rgb, int alpha);
int			clamp_pos(int p, int min, int max);
void		free_viewport(t_data *data);

//timer
void		time_update(void *param);
void		start_timer(t_timer *timer);
void		display_game_infos(void *param);

int			set_default(t_data *data);
char		*str_seed(long int n);

#endif
