/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 10:54:09 by tseche            #+#    #+#             */
/*   Updated: 2026/06/03 12:44:07 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_map(t_data *data)
{
	int	i;

	if (!data->map || !data->map->grid)
		return ;
	i = 0;
	while (i <= data->map->height)
	{
		free(data->map->grid[i++]);
	}
	free(data->map->grid);
	if (data->map->start)
		free(data->map->start);
	if (data->map)
		free(data->map);
}

void	free_texture_paths(t_data *data)
{
	if (data->texture[NO].path)
		free(data->texture[NO].path);
	if (data->texture[SO].path)
		free(data->texture[SO].path);
	if (data->texture[WE].path)
		free(data->texture[WE].path);
	if (data->texture[EA].path)
		free(data->texture[EA].path);
}

void	free_all(t_data *data, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	if (fd != -1)
		close(fd);
	free_map(data);
	free_texture_paths(data);
	if (data->player)
		free(data->player);
	free(data);
}

void	clear_gnl_buffer(int fd)
{
	char	*line;

	if (fd < 0)
		return ;
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
}

void	clean_exit(t_data *data, bool img_destroy)
{
	if (img_destroy)
	{
		if (data->wall_assets[0] != MLX_NULL_HANDLE)
			mlx_destroy_image(data->mlx, data->wall_assets[0]);
		if (data->wall_assets[1] != MLX_NULL_HANDLE)
			mlx_destroy_image(data->mlx, data->wall_assets[1]);
		if (data->wall_assets[2] != MLX_NULL_HANDLE)
			mlx_destroy_image(data->mlx, data->wall_assets[2]);
		if (data->wall_assets[3] != MLX_NULL_HANDLE)
			mlx_destroy_image(data->mlx, data->wall_assets[3]);
		if (data->frame != MLX_NULL_HANDLE)
			mlx_destroy_image(data->mlx, data->frame);
	}
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_context(data->mlx);
	free_all(data, -1);
}
