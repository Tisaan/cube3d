/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 15:57:11 by tseche            #+#    #+#             */
/*   Updated: 2026/05/05 11:36:05 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	map_size(char *name)
{
	int		fd;
	int		size;
	char	*line;

	fd = open(name, O_RDONLY);
	if (fd == -1)
	{
		perror("ERROR");
		return (-ERROR_OPEN);
	}
	size = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!ft_isempty(line))
			size++;
		free(line);
		line = get_next_line(fd);
	}
	if (size == 0)
		return (-INV_MAP);
	close(fd);
	return (size);
}

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

	i = 0;
	find = 0;
	while (map->grid[i])
	{
		j = 0;
		j += skip_spaces(map->grid[i]);
		first = 1;
		while (map->grid[i][j])
		{
			if (map->grid[i][j] == '\n')
				break ;
			if (first && map->grid[i][j] != '1')
			{
				printf("x:%d, y:%d\n", i, j);
				return (-INV_WALL_MAP);
			}
			else
				first = 0;
			if (!around(map, i, j))
			{
				printf("x:%d, y:%d\n", i, j);
				return (-INV_WALL_MAP);
			}
			if (ft_isoneof(map->grid[i][j], "NEWS") && find == 0)
			{
				find = 1;
				map->start[0] = i;
				map->start[1] = j;
				map->start[2] = get_dir(map->grid[i][j]);
			}
			else if (ft_isoneof(map->grid[i][j], "NEWS"))
				return (-TOO_MUCH_STRT);
			j++;
			first = 0;
		}
		i++;
	}
	return (1);
}

int	check_map(t_map *map)
{
	int	err;

	map->start = malloc(sizeof(int) * 3);
	err = walled(map);
	if (!map->start)
		return (-NOT_ENO_STRT);
	return (err);
}

bool	is_pattern_char_present(char *line, char *pat)
{
	int i;

	i = 0;
	while (line && line[i])
	{
		if (ft_isoneof(line[i], pat))
			return (true);
		i++;
	}
	return (false);
}

int	get_map(int fd, t_map *data, int size)
{
	char	*line;
	int		end;
	int		len;
	int		find;
	int		i;

	data->grid = malloc(sizeof(char *) * (size + 1));
	data->height = size;
	
	line = get_next_line(fd);
	end = 0;
	find = 0;
	i = 0;
	while (line)
	{
		while (line && ft_isempty(line))
		{
			if (find)
				end = 1;
			free(line);
			line = get_next_line(fd);
		}
		if (!line)
			break ;
		len = ft_strlen(line);
		if (!is_pattern_char_present(line, "01NEWS") && end)
			return (-NOT_ENO_STRT);
		else if (is_pattern_char_present(line, "01"))
			find = 1;
		else if (skip_pattern(line, " 01NEWS") != len -1)
			return (-INC_CHAR);
		if (len > data->width)
			data->width = len;
		data->grid[i++] = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
	}
	data->grid[i] = NULL; 
	if (!find)
		return (-EMPT_MAP);
	return (1);
}
