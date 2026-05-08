/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 12:21:06 by tseche            #+#    #+#             */
/*   Updated: 2026/05/07 17:19:40 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus.h"

int		moore_neighborhood(int **map, int x, int y)
{
	int	count;

	count = 0;
	if (map[x + 1][y + 1] && ft_isoneof(map[x + 1][y + 1], "15"))
		count++;
	if (map[x + 1][y] && ft_isoneof(map[x + 1][y], "15"))
		count++;
	if (map[x + 1][y - 1] && ft_isoneof(map[x + 1][y - 1], "15"))
		count++;
	if (map[x][y + 1] && ft_isoneof(map[x][y + 1], "15"))
		count++;
	if (map[x][y - 1] && ft_isoneof(map[x][y - 1], "15"))
		count++;
	if (map[x - 1][y + 1] && ft_isoneof(map[x - 1][y + 1], "15"))
		count++;
	if (map[x - 1][y] && ft_isoneof(map[x - 1][y], "15"))
		count++;
	if (map[x - 1][y + 1] && ft_isoneof(map[x - 1][y + 1], "15"))
		count++;
	return (count);
}

void	apply_rule(t_map_simu *map, int x, int y)
{
	int		nb;

	nb = moore_neighborhood(map->map, x, y);
	if (map->map[x][y] == 0 && map->stof == nb)
		map->map[x][y] = 4;
	if (map->map[x][y] == 1 && !between(map->min, map->ftof, nb))
		map->map[x][y] = 5;
	if (map->len == 8)
	{
		if (map->map[x][y] == 2 && map->wtos == nb)
			map->map[x][y] = 6;
	}
}

void	update_simu(t_map_simu *map)
{
	int	x;
	int	y;

	x = 0;
	while (x < map->height)
	{
		y = 0;
		while (y < map->width)
		{
			if (map->map[x][y] == 4)
				map->map[x][y] = 1;
			if (map->map[x][y] == 5)
				map->map[x][y] = 2;
			if (map->map[x][y] == 6)
				map->map[x][y] = 0;
			y++;
		}
		x++;
	}
}



void	wall(t_map_simu *map, int x, int y, int *check)
{
	if (!map->wall && had_space_neighbour(map->map, x, y))
		map->map[x][y] = 1; 
	if (map->wall && had_space_neighbour(map->map, x, y))
	{
		if (map->map[x - 1][y] && map->map[x - 1][y] == 0)
			map->map[x - 1][y] = 1;
		else if (map->map[x-1][y - 1] && map->map[x-1][y - 1] == 0)
			map->map[x-1][y - 1] = 1;
		else if (map->map[x-1][y + 1] && map->map[x-1][y + 1] == 0)
			map->map[x-1][y - 1] = 1;
		else if (map->map[x + 1][y] && map->map[x + 1][y] == 0)
			map->map[x-1][y - 1] = 1;
		else if (map->map[x+1][y - 1] && map->map[x+1][y - 1] == 0)
			map->map[x-1][y - 1] = 1;
		else if (map->map[x+1][y + 1] && map->map[x+1][y + 1] == 0)
			map->map[x-1][y - 1] = 1;
		else if (map->map[x][y - 1] && map->map[x][y - 1] == 0)
			map->map[x-1][y - 1] = 1;
		else if (map->map[x][y + 1] && map->map[x][y + 1] == 0)
			map->map[x-1][y - 1] = 1;
		if (!had_space_neighbour(map->map, x, y))
			*check = 0;
	}
	
}

void	apply_wall(t_map_simu *map)
{
	int	x;
	int	y;
	int check;

	x = 0;
	check = 1;
	while (x < map->height)
	{
		y = 0;
		while (y < map->width)
		{
			if (map->map[x][y] == 1)
				wall(map, x, y, &check);
			y++;
		}
		x++;
	}
	if (!check)
		apply_wall(map);
}

void	simulate(t_map_simu *map)
{
	int	x;
	int	y;

	x = 0;
	while (map->iter)
	{
		while (x < map->height)
		{
			y = 0;
			while (y < map->width)
			{
				apply_rule(map, x, y);
				y++;
			}
			x++;
		}
		update_simu(map);
		map->iter--;
	}
	apply_wall(map);
	place_door(map);
}