/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 15:30:00 by pcaplat           #+#    #+#             */
/*   Updated: 2026/05/01 13:32:28 by pcaplat          ###   ########.fr       */
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

	//check map_path extension
	data.map = NULL;
	if (!ft_strendwith(map_path, ".cub"))
	{
		ft_putstr_fd("Invalid map extension. The map extension must be '.cub'.\n", STDERR_FILENO);
		return (data);
	}
	//parse map_args

	//int	size = map_size(map_path);

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
	data.map = malloc(sizeof(t_map));
	return (data);
}
