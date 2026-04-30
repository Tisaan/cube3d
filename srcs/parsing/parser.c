/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 15:30:00 by pcaplat           #+#    #+#             */
/*   Updated: 2026/04/29 18:57:07 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>

void	free_all(t_data *data)
{
	if (data->map && data->map->grid)
		free(data->map->grid);
	if (data->map)
		free(data->map);
	if (data->texture[NO].path)
		free(data->texture[NO].path);
	if (data->texture[SO].path)
		free(data->texture[SO].path);
	if (data->texture[WE].path)
		free(data->texture[WE].path);
	if (data->texture[EA].path)
		free(data->texture[EA].path);
}

static t_direction_id	get_identifier(char *line)
{
	if (ft_strncmp(line, "NO", 2) == 0)
		return (NO);
	if (ft_strncmp(line, "SO", 2) == 0)
		return (SO);
	if (ft_strncmp(line, "WE", 2) == 0)
		return (WE);
	if (ft_strncmp(line, "EA", 2) == 0)
		return (EA);
	return (INV);
}

static t_prgb	rgb_str_to_int(char	*str)
{
	t_prgb	color;
	int		i;
	int		j;

	i = 0;
	j = 0;
	color.rgb[0] = -1;
	color.rgb[1] = -1;
	color.rgb[2] = -1;
	while (str && str[i])
	{
		while(str && str[i] && !ft_isdigit(str[i]))
			i++;
		if (!str[i])
			break ;
		color.rgb[j] = ft_atoi(&str[i]);
		i += skip_digits(&str[i]);
		j++;
	}
	return (color);
}

static bool	parse_map_data(int fd, t_data *data)
{
	char			*line;
	t_direction_id	id;
	int				i;
	bool			match;

	line = get_next_line(fd);
	while (line)
	{
		i = 0;
		while(ft_strncmp(line, "\n", 1) == 0)
		{
			free(line);
			line = get_next_line(fd);
		}
		i += skip_spaces(&line[i]);
		if (line[i] == '0' || line[i] == '1')
			break ;
		id = get_identifier(&line[i]);
		if (id == INV && (line[i] == 'F' || line[i] == 'C'))
		{
			match = line[i] == 'F';
			data->plans_color[match] = rgb_str_to_int(&line[i]);
			data->plans_color[match].type = match;
		}
		else if (id != INV)
		{
			i += 2;
			i += skip_spaces(line);
			data->texture[id].dir = id;
			data->texture[id].path = ft_strdup(&line[i]);
			if (data->texture[id].path == NULL)
			{
				free(line);
				free_all(data);
				return (false);
			}
		}
		else
		{
			free(line);
			return (false);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (true);
}

t_data	parse(char *map_path)
{
	t_data	data = {0};
	int		fd;

	//check map_path extension
	data.map = NULL;
	if (!ft_strendwith(map_path, ".cub"))
	{
		ft_putstr_fd("Invalid map extension. The map extension must be '.cub'.\n", STDERR_FILENO);
		return (data);
	}
	//parse map_args
	fd = open(map_path, O_RDONLY);
	if (fd == -1)
	{
		perror("Error");
		return (data);
	}
	if (!parse_map_data(fd, &data))
	{
		close(fd);
		return (data);
	}
	data.map = malloc(sizeof(t_map));
	return (data);
}
