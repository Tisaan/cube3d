/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 11:08:21 by pcaplat           #+#    #+#             */
/*   Updated: 2026/05/06 19:42:15 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H
# include "cub3d.h"

void	display_map_data(t_data data);
void	display_player_data(t_player *player);
void	init_pip_boy(t_img *img, t_data *data);
void	ft_print_error(const char *msg);
int		render_2D_map(t_data *data);

#endif
