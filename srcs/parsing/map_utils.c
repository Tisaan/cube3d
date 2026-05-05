/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 12:40:34 by tseche            #+#    #+#             */
/*   Updated: 2026/05/05 15:46:05 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	get_dir(int c)
{
	if (c == 'N')
		return (NO);
	else if (c == 'S')
		return (SO);
	else if (c == 'E')
		return (EA);
	return (WE);
}

bool	around(t_map *map, int x, size_t y)
{
	char	*line;

	line = map->grid[x];
	if (line[y] == '1' || ft_isspace(line[y]))
		return (true);
	else if (y == ft_strlen(line) || x == 0 || x == map->height)
		return (false);
	else if (ft_isoneof(map->grid[x - 1][y], " "))
		return (false);
	else if (ft_isoneof(map->grid[x - 1][y - 1], " "))
		return (false);
	else if (ft_isoneof(map->grid[x - 1][y + 1], " "))
		return (false);
	else if (ft_isoneof(map->grid[x + 1][y], " \t\n"))
		return (false);
	else if (ft_isoneof(map->grid[x + 1][y - 1], " "))
		return (false);
	else if (ft_isoneof(map->grid[x + 1][y + 1], " "))
		return (false);
	else if (ft_isoneof(map->grid[x][y - 1], " \t\n"))
		return (false);
	else if (ft_isoneof(map->grid[x][y + 1], " \t\n"))
		return (false);
	return (true);
}

int	walled(t_map *map)
{
	int	i;
	int	j;
	int	first;
	int	find;
	int	err;

	i = 0;
	find = 0;
	while (map->grid[i])
	{
		j = 0;
		j += skip_spaces(map->grid[i]);
		first = 1;
		err = line_wall(map, (int *)((int [2]){i, j}), &find, &first);
		if (err < 0)
			return (err);
		i++;
	}
	return (1);
}

int	check_map(t_map *map, int fd)
{
	int	err;

	close(fd);
	map->start = malloc(sizeof(int) * 3);
	err = walled(map);
	if (!map->start)
		return (-NOT_ENO_STRT);
	return (err);
}

bool	is_pattern_char_present(char *line, char *pat)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		if (ft_isoneof(line[i], pat))
			return (true);
		i++;
	}
	return (false);
}
