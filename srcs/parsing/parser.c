/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 15:30:00 by pcaplat           #+#    #+#             */
/*   Updated: 2026/05/12 15:52:17 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/utils.h"
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>

int	map_size(char *name);

t_map	*init_map_metadata(int size)
{
	t_map	*map;

	map = ft_calloc(sizeof(t_map), 1);
	if (!map)
		throw_error(ERROR_MALLOC);
	if (!map)
		return (NULL);
	map->grid = ft_calloc(sizeof(char *), (size + 1));
	if (!map->grid)
		throw_error(-ERROR_MALLOC);
	if (!map->grid)
		return (NULL);
	map->start = NULL;
	return (map);
}

t_data	*parse_map(int fd, t_data *data, int size_file)
{
	int		count;
	int		err;

	count = 0;
	data->map = init_map_metadata(size_file - count);
	if (!data->map)
		return (NULL);
	err = parse_map_data(fd, data, &count);
	if (err < 0)
	{
		close(fd);
		throw_error(err);
		return (NULL);
	}
	data->map->height = size_file - count;
	err = get_map(fd, data->map);
	if (err < 0)
		throw_error(err);
	if (err < 0)
		return (NULL);
	err = check_map(data->map);
	if (err < 0)
		throw_error(err);
	if (err < 0)
		return (NULL);
	return (data);
}

t_data	parse(char *map_path)
{
	t_data	data;
	int		fd;
	int		size_file;
	void	*truc;

	data.map = NULL;
	if (!ft_strendwith(map_path, ".cub"))
	{
		throw_error(INC_EXT);
		return ((t_data){0});
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
		throw_error(ERROR_OPEN);
		return ((t_data){0});
	}
	truc = parse_map(fd, &data, size_file);
	if (!truc)
	{
		free_all(&data, fd);
		close(fd);
		return ((t_data ){0});
	}
	close(fd);
	return (data);
}
