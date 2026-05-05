/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 15:57:11 by tseche            #+#    #+#             */
/*   Updated: 2026/05/05 16:31:32 by tseche           ###   ########.fr       */
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

	len = ft_strlen(line);
	if (check_char_present_map(line, find, len) < 0)
		return (check_char_present_map(line, find, len));
	if (len > data->width)
		data->width = len;
	data->grid[i] = ft_strdup(line);
	free(line);
	if (!data->grid[i])
		return (-ERROR_MALLOC);
	return (0);
}

int	get_map(int fd, t_map *data)
{
	char	*line;
	int		find[1];
	int		i;
	int		err;

	line = get_next_line(fd);
	i = 0;
	*find = 0;
	while (line)
	{
		line = repline(line, fd, find, 1);
		if (!line)
			break ;
		err = validate(line, data, i++, find);
		if (err < 0)
			return (err);
		line = get_next_line(fd);
		data->grid[i] = NULL;
	}
	if (!*find)
		return (-EMPT_MAP);
	return (1);
}
