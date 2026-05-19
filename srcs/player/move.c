/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 11:15:24 by pcaplat           #+#    #+#             */
/*   Updated: 2026/05/19 13:39:11 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/player.h"

static bool	is_wall(t_data *data, float x, float y)
{
	int	tile_x;
	int	tile_y;

	tile_x = (int)(x / WALL_SIZE);
	tile_y = (int)(y / WALL_SIZE);
	if (tile_x < 0 || tile_x >= (int)ft_strlen(data->map->grid[tile_y]))
		return (true);
	if (tile_y < 0 || tile_y >= data->map->height)
		return (true);
	if (data->map->grid[tile_y][tile_x] == '1'
		|| data->map->grid[tile_y][tile_x] == ' ')
		return (true);
	return (false);
}

static bool	is_colliding(t_data *data, t_vect pos)
{
	if (is_wall(data, pos.x, pos.y - PLAYER_RADIUS))
		return (true);
	if (is_wall(data, pos.x, pos.y + PLAYER_RADIUS))
		return (true);
	if (is_wall(data, pos.x - PLAYER_RADIUS, pos.y))
		return (true);
	if (is_wall(data, pos.x + PLAYER_RADIUS, pos.y))
		return (true);
	return (false);
}

void	update_player_pos(void *param)
{
	t_data		*data;
	t_player	*p;
	t_vect		new_pos;

	data = (t_data *)param;
	p = data->player;
	if (p->dest.x == 0.0f && p->dest.y == 0.0f)
		return ;
	set_vect(&new_pos, (p->pos.x + p->dest.x), 0.0f);
	if (!is_colliding(data, new_pos))
		p->pos.x = new_pos.x;
	new_pos.y = p->pos.y + p->dest.y;
	if (!is_colliding(data, new_pos))
		p->pos.y = new_pos.y;
}
