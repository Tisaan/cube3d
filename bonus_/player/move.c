/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: von <von@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 11:15:24 by pcaplat           #+#    #+#             */
/*   Updated: 2026/06/02 11:00:20 by von              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/player.h"

static void	switch_player_dest(t_player *p, float speed, t_keys keys)
{
	if (keys.w)
	{
		p->dest.x += p->dir.x * speed;
		p->dest.y += p->dir.y * speed;
	}
	if (keys.s)
	{
		p->dest.x -= p->dir.x * speed;
		p->dest.y -= p->dir.y * speed;
	}
	if (keys.d)
	{
		p->dest.x += -p->dir.y * speed;
		p->dest.y += p->dir.x * speed;
	}
	if (keys.a)
	{
		p->dest.x -= -p->dir.y * speed;
		p->dest.y -= p->dir.x * speed;
	}
}

static void	set_player_dest(t_data *data)
{
	t_player	*p;
	t_keys		keys;
	float		speed;

	p = data->player;
	speed = data->delta * PLAYER_SPEED;
	keys = data->keys;
	set_vect(&p->dest, 0.0f, 0.0f);
	switch_player_dest(p, speed, keys);
	normalize(&p->dest, speed);
}

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
	set_player_dest(data);
	if (p->dest.x == 0.0f && p->dest.y == 0.0f)
		return ;
	set_vect(&new_pos, p->pos.x + p->dest.x, p->pos.y);
	if (!is_colliding(data, new_pos))
		p->pos.x = new_pos.x;
	set_vect(&new_pos, p->pos.x, p->pos.y + p->dest.y);
	if (!is_colliding(data, new_pos))
		p->pos.y = new_pos.y;
}
