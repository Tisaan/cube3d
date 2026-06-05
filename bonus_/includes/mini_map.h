/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 15:28:15 by pcaplat           #+#    #+#             */
/*   Updated: 2026/06/05 18:33:19 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_MAP_H
# define MINI_MAP_H
# include "../includes/cub3d.h"

int		set_viewport(t_player *player, t_map *map);
void	set_mini_map_pixels(t_data *data);

#endif
