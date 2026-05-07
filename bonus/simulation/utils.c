/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 15:15:18 by tseche            #+#    #+#             */
/*   Updated: 2026/05/07 17:39:44 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus.h"

bool	between(int a, int b, int c)
{
	return ((c >= a && c <= b) || (c >= b && c <= a));
}

bool	had_space_neighbour(int **map, int x, size_t y)
{
	if (map[x - 1][y] && map[x - 1][y] == 0)
		return (true);
	else if (map[x-1][y - 1] && map[x-1][y - 1] == 0)
		return (true);
	else if (map[x-1][y + 1] && map[x-1][y + 1] == 0)
		return (true);
	else if (map[x + 1][y] && map[x + 1][y] == 0)
		return (true);
	else if (map[x+1][y - 1] && map[x+1][y - 1] == 0)
		return (true);
	else if (map[x+1][y + 1] && map[x+1][y + 1] == 0)
		return (true);
	else if (map[x][y - 1] && map[x][y - 1] == 0)
		return (true);
	else if (map[x][y + 1] && map[x][y + 1] == 0)
		return (true);
	return (false);
}

char	**get_map_from_simu(t_map_simu *map)
{
	char	**nmap;
	int		i;
	int		j;

	nmap = ft_calloc(sizeof(char *), (map->height));
	i = 0;
	while (i < map->height)
	{
		j = 0;
		nmap[i] = ft_calloc(sizeof(char), map->width);
	
		while (j < map->width)
		{
			if (map->map[i][j] == 0)
				nmap[i][j] = ' ';
			else if (map->map[i][j] == 1)
				nmap[i][j] = '0';
			else if (map->map[i][j] == 2)
				nmap[i][j] = '1';
			else if (map->map[i][j] == 3)
				nmap[i][j] = 'D';
			j++;
		}
		i++;
	}
}
