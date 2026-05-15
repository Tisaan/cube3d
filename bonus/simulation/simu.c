/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: von <von@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 12:21:06 by tseche            #+#    #+#             */
/*   Updated: 2026/05/13 21:20:57 by von              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus.h"
#include <stdio.h>
#include <unistd.h>

int		moore_neighborhood(t_map_simu *map, int x, int y)
{
	int	count;
	const int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    const int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

	count = 0;
	
    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        // Check if the neighbor is within grid boundaries
        if (nx >= 0 && nx < map->width && ny >= 0 && ny < map->height)
		{
			// printf("x:%d, y:%d, height:%d, width:%d\n", nx, ny, map->height, map->width);
			if (map->map[nx][ny] == '1')
            	count++;
        }
	}
	return (count);
}

void	apply_rule(t_map_simu *map, int x, int y)
{
	int		nb;

	nb = moore_neighborhood(map, x, y);
	if (map->map[x][y] == '0' && nb == 3)
		map->map[x][y] += 4;
	if (map->map[x][y] == '1' && between(2, 3, nb))
		map->map[x][y] += 4;
}

void	update_simu(t_map_simu *map)
{
	int	x;
	int	y;

	x = 0;
	while (x <= map->height)
	{
		y = 0;
		while (y <= map->width)
		{
			if (map->map[x][y] == ('0' + 4))
				map->map[x][y] = '1';
			else if (map->map[x][y] == ('1' + 4))
				map->map[x][y] = '1';
			else
			 	map->map[x][y] = '0';
			y++;
		}
		x++;
	}
}



void	wall(t_map_simu *map, int x, int y)
{
	int	i;
	int	j;
	// if (map->wall == 0 && had_space_neighbour(map, x, y))
	// 	map->map[x][y] = '1'; 
	if (had_space_neighbour(map, x, y))
	{
		i = -1;
		while (i <= 1)
		{
			j = -1;
			while (j <= 1)
			{
				if (map->map[(map->height + x + i) % map->height][(map->width + y + j) % map->width] == '0')
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
	int i;

	x = 1;
	while (x <= map->height)
	{
		y = 1;
		while (y <= map->width)
		{
			if (map->map[x][y] == '0')
				wall(map, x, y);
			y++;
		}
		x++;
	}
	i = 0;
	while (i <= map->width)
	{
		if (map->map[0][i] == '0')
			map->map[0][i] = '1';
		if (map->map[map->height][i] == '0')
			map->map[map->height][i] = '1';
		i++;
	}
	i = 0;
	while (i <= map->height)
	{
		if (map->map[i][0] == '0')
			map->map[i][0] = '1';
		if (map->map[i][map->width] == '0')
			map->map[i][map->width] = '1';
		i++;
	}
}

void	update_map(t_map_simu *map)
{
	int i;
	int j;

	i = 0;
	while (i <= map->height)
	{
		j = 0;
		while (j <= map->width)
		{
			if (map->map[i][j] == '0')
				map->map[i][j] = ' ';
			else if (map->map[i][j] == '1')
				map->map[i][j] = '0';
			else
				map->map[i][j] = '1';
			j++;
		}
		i++;
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
		// if (map->iter % 4 == 0)
		// {
		// 	printf("iter[%d]\n", iter - map->iter);
		// 	for (int i = 0; map->map[i]; i++)
		// 		printf("%s\n", map->map[i]);
		// }
		map->iter--;
	}
	update_map(map);
	printf("before wall\n");
	for (int i = 0; i < map->height; i++)
		printf("%s\n", map->map[i]);
	apply_wall(map);
	place_door(map);
}
