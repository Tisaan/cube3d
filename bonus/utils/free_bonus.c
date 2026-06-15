/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: von <von@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 10:54:09 by tseche            #+#    #+#             */
/*   Updated: 2026/06/15 14:06:35 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

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
	if (data->map->viewport)
	{
		i = 0;
		while (data->map->viewport[i])
		{
			free(data->map->viewport[i]);
			i++;
		}
	}
	free(data->map->grid);
	i = 0;
	while (i <= data->map->height)
	{
		if (data->map_door && data->map_door[i])
			free(data->map_door[i]);
		i++;
	}
	free(data->map_door);
	if (data->map->start)
		free(data->map->start);
	if (data->seed)
		free(data->seed);
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
	if (data->mouse_pos)
		free(data->mouse_pos);
	if (data)
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
		if (data->door_asset[0] != MLX_NULL_HANDLE)
			mlx_destroy_image(data->mlx, data->door_asset[0]);
		if (data->door_asset[1] != MLX_NULL_HANDLE)
			mlx_destroy_image(data->mlx, data->door_asset[1]);
		if (data->mini_map != MLX_NULL_HANDLE)
			mlx_destroy_image(data->mlx, data->mini_map);
		destroy_sprite_assets(data);
	}
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_context(data->mlx);
	free_all(data, -1);
}
