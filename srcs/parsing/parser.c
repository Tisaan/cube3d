/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 15:30:00 by pcaplat           #+#    #+#             */
/*   Updated: 2026/05/04 16:38:11 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>

int	map_size(char *name);

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
	
	count = 0;
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
		throw_error(ret);
		return (data);
	}
	data.map = ft_calloc(sizeof(t_map), 1);
	err = get_map(fd, data.map, size_file - count);
	if (err < 0)
	{
		throw_error(err);
		return ((t_data){0});
	}
	close(fd);
	// printf("MAP:\n");
	// for (int i = 0; data.map->grid[i]; i++)
	// 	printf("%s", data.map->grid[i]);
	
	err = check_map(data.map);
	if (err < 0)
	{
		// voir si return ou exit
		throw_error(err);
		return ((t_data){0});
	}
	printf("start:\n x:%d\ny:%d\ndir:%d\n", data.map->start[0], data.map->start[1], data.map->start[2]);
	
	return (data);
}
