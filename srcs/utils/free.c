/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 10:54:09 by tseche            #+#    #+#             */
/*   Updated: 2026/05/06 20:16:52 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// void	free_map(t_map *map)
// {
// }

void	free_all(t_data *data, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	if (data->map && data->map->grid)
	{
		for (int i = 0; i < data->map->height; i++)
			free(data->map->grid[i]);
		free(data->map->grid);
	}
	if (data->map->start)
		free(data->map->start);
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

void	clean_exit(t_data *data)
{
	mlx_destroy_image(data->mlx, data->wall_assets[0]);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_context(data->mlx);
	free_all(data, -1);
}
