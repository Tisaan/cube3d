/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 15:28:15 by pcaplat           #+#    #+#             */
/*   Updated: 2026/06/15 14:35:02 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_MAP_BONUS_H
# define MINI_MAP_BONUS_H
# include "../includes/cub3d_bonus.h"
# include "../includes/bonus.h"

int		set_viewport(t_player *player, t_map *map);
void	set_mini_map_pixels(t_data *data);
void	clear_viewport(t_map *map, int i);
int		fill_end_with_space(t_map *map, int *i);
int		fill_start_with_space(t_map *map, int *i, int *map_y);
int		fill_viewport(t_player *player, t_map *map, t_point view);
void	toogle_door_state(void *param);

#endif
