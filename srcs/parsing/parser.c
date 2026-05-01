/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 15:30:00 by pcaplat           #+#    #+#             */
/*   Updated: 2026/05/01 13:21:07 by tseche           ###   ########.fr       */
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

static bool	parse_map_data(int fd, t_data *data, int *count)
{
	char			*line;
	t_direction_id	id;
	int				i;
	bool			match;

	line = get_next_line(fd);
	*count += 1;
	while (line)
	{
		i = 0;
		while(ft_isempty(line))
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
			i += skip_spaces(&line[i]);
			data->texture[id].dir = id;
			data->texture[id].path = get_path(&line[i]);
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
		*count  += 1;
	}
	return (true);
}

t_data	parse(char *map_path)
{
	t_data	data = {0};
	int		fd[2];
	int		count;
	int		size_file;
	int		err;

	//check map_path extension
	data.map = NULL;
	if (!ft_strendwith(map_path, ".cub"))
	{
		ft_putstr_fd("Invalid map extension. The map extension must be '.cub'.\n", STDERR_FILENO);
		return (data);
	}
	

	size_file = map_size(map_path);
	if (size_file < 0)
	{
		throw_error(size_file);
		return ((t_data){0});
	}
	fd[0] = open(map_path, O_RDONLY);
	fd[1] = open(map_path, O_RDONLY);
	if (fd[0] == -1 || fd[1] == -1)
	{
		perror("Error");
		return (data);
	}
	if (!parse_map_data(fd[1], &data, &count))
	{
		close(fd[0]);
		close(fd[1]);
		return (data);
	}
	close(fd[1]);
	data.map = ft_calloc(sizeof(t_map), 1);
	err = get_map(fd[0], data.map, size_file, count);
	if (err < 0)
	{
		throw_error(err);
		return ((t_data){0});
	}
	close(fd[0]);
	err = check_map(data.map);
	if (err < 0)
	{
		// voir si return ou exit
		throw_error(err);
		return ((t_data){0});
	}
	
	// printf("MAP:\n");
	// for (int i= 0; data.map->grid[i]; i++)
	// 	printf("%s", data.map->grid[i]);
	// printf("start:\n x:%d\ny:%d\ndir:%d\n", data.map->start[0], data.map->start[1], data.map->start[2]);
	return (data);
}
