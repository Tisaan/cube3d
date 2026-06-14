/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: von <von@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 17:19:07 by tseche            #+#    #+#             */
/*   Updated: 2026/06/14 12:00:46 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bonus.h"

bool	door_placeable(t_map_simu *map, int x, int y)
{
	if (map->map[x + 1][y] &&
		map->map[x - 1][y] &&
		map->map[x][y + 1] &&
		map->map[x][y - 1])
	{
		if (map->map[x + 1][y] == '0' &&
			map->map[x - 1][y] == '0' &&
			map->map[x][y + 1] == '1' &&
			map->map[x][y - 1] == '1')
			return (true);
		else if (map->map[x + 1][y] == '1' &&
			map->map[x - 1][y] == '1' &&
			map->map[x][y + 1] == '0' &&
			map->map[x][y - 1] == '0')
			return (true);
	}
	return (false);
}

void	place_door(t_map_simu *map)
{
	int		x;
	int		y;
	float	ran;

	x = 1;
	while (x < map->height - 1)
	{
		y = 1;
		while (y < map->width - 1)
		{
			if (door_placeable(map, x, y))
			{
				ran = (float)rand() / (float)RAND_MAX;
				if (ran <= map->door)
					map->map[x][y] = 'D';
			}
			y++;
		}
		x++;
	}
}

static char	*set_doors_map_line(char *base_line)
{
	char	*line;
	int		i;

	line = malloc(sizeof(char) * ((int)ft_strlen(base_line) + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (base_line[i])
	{
		if (base_line[i] == 'D')
		{
			line[i] = '1';
			base_line[i] = '0';
		}
		else
		 	line[i] = ' ';
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	**set_doors_map(t_data *data)
{
	char	**doors_map;
	int		i;

	doors_map = malloc(sizeof(char *) * (data->map->height + 1));
	if (!doors_map)
		return (NULL);
	i = 0;
	while (i < data->map->height)
	{
		doors_map[i] = set_doors_map_line(data->map->grid[i]);
		if (!doors_map[i])
		{
			ft_freeptr((void **)doors_map);
			return (NULL);
		}
		i++;
	}
	doors_map[i] = NULL;
	for (int i = 0; doors_map[i]; i++)
		printf("%s\n", doors_map[i]);
	return (doors_map);
}
