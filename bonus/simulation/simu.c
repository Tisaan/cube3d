/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 12:21:06 by tseche            #+#    #+#             */
/*   Updated: 2026/05/09 18:08:39 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus.h"

int		moore_neighborhood(t_map_simu *map, int x, int y)
{
	int	count;
	int	j;
	int	i;

	count = 0;
	i = -1;
	while (i <= 1)
	{
		j = -1;
		while (j <= 1)
		{
			if (map->map[(map->height + x + i) % map->height][(map->width + y + j) % map->width] && (i != 0 && j != 0))
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

void	apply_rule(t_map_simu *map, int x, int y)
{
	int		nb;

	nb = moore_neighborhood(map, x, y);
	if (map->map[x][y] == ' ' && map->stof == nb)
		map->map[x][y] += 4;
	if (map->map[x][y] == '0' && between(map->min, map->ftof, nb))
		map->map[x][y] += 4;
	if (map->len == 8)
	{
		if (map->map[x][y] == '1' && map->wtos == nb)
			map->map[x][y] += 4;
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
			if (map->map[x][y] == (' ' + 4))
				map->map[x][y] = '0';
			if (map->map[x][y] == ('0' + 4))
				map->map[x][y] = '1';
			if (map->map[x][y] == ('1' + 4))
				map->map[x][y] = ' ';
			y++;
		}
		x++;
	}
}



void	wall(t_map_simu *map, int x, int y)
{
	int	i;
	int	j;
	if (map->wall == 0 && had_space_neighbour(map, x, y))
		map->map[x][y] = '1'; 
	if (map->wall == 1 && had_space_neighbour(map, x, y))
	{
		i = -1;
		while (i <= 1)
		{
			j = -1;
			while (j <= 1)
			{
				if (map->map[(map->height + x + i) % map->height][(map->width + y + j) % map->width] == ' ')
					map->map[(map->height + x + i) % map->height][(map->width + y + j) % map->width] = '1';
				j++;
			}
			i++;
		}
	}
	
}

void	apply_wall(t_map_simu *map)
{
	int	x;
	int	y;

	x = 0;
	while (map->map[x])
	{
		y = 0;
		while (map->map[x][y])
		{
			if (map->map[x][y] == '0')
				wall(map, x, y);
			y++;
		}
		x++;
	}
}

void	simulate(t_map_simu *map)
{
	int	x;
	int	y;
	int iter = map->iter;

	while (map->iter)
	{
		x = 0;
		while (map->map[x])
		{
			y = 0;
			while (map->map[x][y])
			{
				apply_rule(map, x, y);
				y++;
			}
			x++;
		}
		update_simu(map);
		printf("iter[%d]\n", iter - map->iter);
		for (int i = 0; map->map[i] && i < 10; i++)
			printf("%s\n", map->map[i]);
		map->iter--;
	}
	apply_wall(map);
	place_door(map);
}