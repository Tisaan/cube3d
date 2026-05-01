/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 15:57:11 by tseche            #+#    #+#             */
/*   Updated: 2026/05/01 10:42:14 by tseche           ###   ########.fr       */
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
		return (-10);
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

int	get_start(t_map *map)
{
	int i;
	int	j;
	int	find;

	i = 0;
	find = 0;
	while (map->grid[i])
	{
		j = 0;
		while (map->grid[i][j])
		{
			if (ft_isoneof(map->grid[i][j], "NEWS") && find == 0)
			{
				find = 1;
				map->start = (int [3]){i, j, get_dir(map->grid[i][j])};
			}
			else if (ft_isoneof(map->grid[i][j], "NEWS"))
				return (-8);
			j++;
		}
		i++;
	}
	return (1);
}

bool	around(t_map *map, int x, size_t y)
{
	char	*line;

	line = map->grid[x];
	if (line[y] == '1')
		return (true);
	else if (y == ft_strlen(line) || x == 0 || x == map->height)
		return (false);
	else if (!ft_isoneof(map->grid[x - 1][y], "01"))
		return (false);
	else if (!ft_isoneof(map->grid[x + 1][y], "01"))
		return (false);
	else if (!ft_isoneof(map->grid[x][y - 1], "01"))
		return (false);
	else if (!ft_isoneof(map->grid[x][y + 1], "01"))
		return (false);
	return (true);
}

int	walled(t_map *map)
{
	int	i;
	int	j;
	int	first;

	i = 0;
	while (map->grid[i])
	{
		j = 0;
		while (map->grid[i][j])
		{
			j += skip_spaces(map->grid[i]);
			first = 1;
			if (first && map->grid[i][j] != '0')
				return (-6);
			else
				first = 0;
			if (!around(map, i, j))
				return (-6);
			j++;
		}
		i++;
	}
	return (1);
}

int	get_map(int fd, t_map *data, int count)
{
	char	*line;
	int		len;
	int		end;
	int		find;
	int		i;

	data->grid = malloc(sizeof(char *) * (count + 1));
	data->height = count;
	line = get_next_line(fd);
	while (ft_isempty(line))
	{
		free(line);
		line = get_next_line(fd);
	}
	end = 0;
	find = 0;
	i = 0;
	while (line)
	{
		while (ft_isempty(line))
		{
			end = 1;
			free(line);
			line = get_next_line(fd);
		}
		if (!line)
			break ;
		len = ft_strlen(line);
		if (!ft_strnstr(line, "01NEWS", len) && end)
			return (-7);
		else if (ft_strnstr(line, "01", len))
			find = 1;
		else if (skip_pattern(line, " 01NEWS") != len -1)
			return (-3);
		if (len > data->width)
			data->width = ft_strlen(line);
		data->grid[i++] = line;
	}
	data->grid[count] = NULL; 
	if (!find)
		return (-4);
	return (1);
}
