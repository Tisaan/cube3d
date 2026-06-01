/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 15:57:11 by tseche            #+#    #+#             */
/*   Updated: 2026/06/01 11:39:38 by pcaplat          ###   ########.fr       */
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
		size += !ft_isempty(line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	if (size == 0)
		return (-INV_MAP);
	close(fd);
	return (size);
}

int	validate(char *line, t_map *data, int i, int *find)
{
	int		len;
	int		res;

	len = ft_strlen(line) - 1;
	res = check_char_present_map(line, find, len);
	if (res < 0)
		return (res);
	if (len > data->width)
		data->width = len;
	data->grid[i] = ft_strndup(line, 0, ft_strlen(line) - 2);
	free(line);
	if (!data->grid[i])
		return (-ERROR_MALLOC);
	return (0);
}

int	get_map(int fd, t_map *data, int i)
{
	char	*line;
	int		find[2];
	int		err;

	line = get_next_line(fd);
	*find = 0;
	find[1] = 0;
	while (line)
	{
		line = repline(line, fd, find, 1);
		if (!line || *find > 1)
			break ;
		err = validate(line, data, i++, find);
		if (err < 0)
		{
			free(line);
			return (err);
		}
		line = get_next_line(fd);
	}
	free(line);
	if (!*find || *find > 1)
		return ((*find + 3) * -1);
	return (1);
}
