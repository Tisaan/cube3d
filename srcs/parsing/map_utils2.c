/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 14:46:51 by tseche            #+#    #+#             */
/*   Updated: 2026/05/05 15:48:02 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	*repline(char *line, int fd, int *rep, int count)
{
	if (count)
		*rep = 0;
	while (line && ft_isempty(line))
	{
		if (count)
			*rep += 1;
		free(line);
		get_next_line(fd);
	}
	return (line);
}

int	check_char_present_map(char *line, int *find, int len)
{
	if (!is_pattern_char_present(line, "01NEWS") && *find > 1)
		return (-NOT_ENO_STRT);
	else if (is_pattern_char_present(line, "01") && !*find)
		*find = 1;
	else if (skip_pattern(line, " 01NEWS") != len -1)
		return (-INC_CHAR);
	return (1);
}

int	line_wall(t_map *map, int *ij, int *first, int *find)
{
	while (map->grid[ij[0]][ij[1]])
	{
		if (map->grid[ij[0]][ij[1]] == '\n')
			continue ;
		if (*first && map->grid[ij[0]][ij[1]] != '1')
			return (-INV_WALL_MAP);
		else
			*first = 0;
		if (!around(map, ij[0], ij[1]))
			return (-INV_WALL_MAP);
		if (ft_isoneof(map->grid[ij[0]][ij[1]], "NEWS") && *find == 0)
		{
			*find = 1;
			map->start[0] = ij[0];
			map->start[1] = ij[1];
			map->start[2] = get_dir(map->grid[ij[0]][ij[1]]);
		}
		else if (ft_isoneof(map->grid[ij[0]][ij[1]], "NEWS"))
			return (-TOO_MUCH_STRT);
		ij[1]++;
		*first = 0;
	}
	return (0);
}
