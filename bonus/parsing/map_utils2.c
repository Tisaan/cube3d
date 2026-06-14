/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 14:46:51 by tseche            #+#    #+#             */
/*   Updated: 2026/06/14 09:40:19 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*repline(char *line, int fd, int *rep, int count)
{
	while (line && ft_isempty(line))
	{
		if (count)
			*rep += 1;
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}

int	check_char_present_map(char *line, int *find, int len)
{
	if (!is_pattern_char_present(line, "01NEWS") && *find > 1)
		return (-NOT_ENO_STRT);
	else if (is_pattern_char_present(line, "01") && !*find)
		*find = 1;
	else if (skip_pattern(line, " 0D1NEWS") == len)
		find[1] = 1;
	else if (skip_pattern(line, " 0D1NEWS") != len -1)
		return (-INC_CHAR);
	return (1);
}

static bool	check_end_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	i--;
	if (line[i] == '1')
		return (true);
	else if (line[i] == ' ')
	{
		while (i >= 0 && line[i] == ' ')
			i--;
		if (i >= 0 && line[i] == '1')
			return (true);
		return (false);
	}
	return (false);
}

int	line_wall(t_map *map, int *ij, int *first, int *find)
{
	while (map->grid[ij[0]][ij[1]])
	{
		if (map->grid[ij[0]][ij[1]] == '\n')
			break ;
		if (*first && map->grid[ij[0]][ij[1]] != '1')
			return (-INV_WALL_MAP);
		else
			*first = 0;
		if (!check_end_line(map->grid[ij[0]]) || !around(map, ij[0], ij[1]))
			return (-INV_WALL_MAP);
		if (ft_isoneof(map->grid[ij[0]][ij[1]], "NEWS") && *find == 0)
		{
			*find = 1;
			map->start[0] = ij[0];
			map->start[1] = ij[1];
			map->start[2] = get_dir(map->grid[ij[0]][ij[1]]);
			map->grid[ij[0]][ij[1]] = '0';
		}
		else if (ft_isoneof(map->grid[ij[0]][ij[1]], "NEWS"))
			return (-TOO_MUCH_STRT);
		ij[1]++;
		*first = 0;
	}
	return (0);
}

bool	around_step(t_map *map, int x, size_t y)
{
	if ((int)y * WALL_SIZE <= map->width
		&& ft_isoneof(map->grid[x + 1][y], " \t\n"))
		return (false);
	else if (x + 1 <= map->height / WALL_SIZE
		&& ft_isoneof(map->grid[x + 1][y - 1], " \t\n"))
		return (false);
	else if ((int)(y + 1 * WALL_SIZE) <= map->width
		&& ft_isoneof(map->grid[x + 1][y + 1], " \t\n"))
		return (false);
	else if (ft_isoneof(map->grid[x][y - 1], " \t\n"))
		return (false);
	else if (ft_isoneof(map->grid[x][y + 1], " \t\n"))
		return (false);
	return (true);
}
