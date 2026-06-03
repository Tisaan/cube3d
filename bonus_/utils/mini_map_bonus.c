/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 13:07:01 by pcaplat           #+#    #+#             */
/*   Updated: 2026/06/03 13:22:28 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	**set_viewport(t_map *map, t_player *player, int size)
{
	char	**viewport;
	int		x;
	int		y;

	viewport = malloc(sizeof(char *) * size);
	if (!viewport)
		return (NULL);
	return (viewport);
}

bool	set_mini_map_pixels(t_data *data)
{
	int		wall_size;
	int		player_size;
	char	**viewport;

	wall_size = MINI_MAP_SIZE / 10;
	player_size = wall_size / 2;
	viewport = set_viewport(data->map, data->player);
}
