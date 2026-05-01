/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 15:30:00 by pcaplat           #+#    #+#             */
/*   Updated: 2026/05/01 15:59:06 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>

int	map_size(char *name);

int	check_map_data(t_data data)
{
	t_texture_path	*texture;
	t_prgb			*colors;

	texture = data.texture;
	colors = data.plans_color;
	if (texture[0].path == NULL || texture[1].path == NULL || texture[2].path == NULL ||
		texture[3].path == NULL)
		return (-MISS_TEXTURE);
	if (colors[0].type == EMPT || colors[1].type == EMPT)
		return (-MISS_COLOR);
	return (NO_ERROR);
}

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

t_data	parse(char *map_path)
{
	t_data	data = {0};
	int		fd;
	int		ret;
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
	fd = open(map_path, O_RDONLY);
	if (fd == -1)
	{
		perror("Error");
		return (data);
	}
	ret = parse_map_data(fd, &data, &count);
	if (ret < 0)
	{
		close(fd);
		ft_putstr_fd((char *)g_errors[ret * -1], 2);
		return (data);
	}
	ret = check_map_data(data);
	if (ret < 0)
	{
		ft_putstr_fd((char *)g_errors[ret * -1], 2);
		return (data);
	}
	close(fd);
	data.map = ft_calloc(sizeof(t_map), 1);
	err = get_map(fd, data.map, size_file, count);
	if (err < 0)
	{
		throw_error(err);
		return ((t_data){0});
	}
	close(fd);
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
