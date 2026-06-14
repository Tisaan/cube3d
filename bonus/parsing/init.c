/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 11:56:21 by pcaplat           #+#    #+#             */
/*   Updated: 2026/06/14 14:59:04 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/mini_map.h"

bool	init_window(mlx_context mlx, mlx_window *win, t_win_infos *infos)
{
	infos->title = "cub3D";
	infos->width = WIN_WIDTH;
	infos->height = WIN_HEIGHT;
	infos->is_fullscreen = false;
	infos->is_resizable = false;
	*win = mlx_new_window(mlx, infos);
	if (*win == MLX_NULL_HANDLE)
		return (false);
	mlx_set_font_scale(mlx, "default", FONT_SIZE);
	return (true);
}

void	init_map_data(t_data *data)
{
	data->texture[0].path = NULL;
	data->texture[1].path = NULL;
	data->texture[2].path = NULL;
	data->texture[3].path = NULL;
	data->plans_color[0].type = EMPT;
	data->plans_color[1].type = EMPT;
}

static void	destroy_wall_assets(t_data *data, int i)
{
	int	j;

	j = 0;
	while (j < i - 1)
		mlx_destroy_image(data->mlx, data->wall_assets[j++]);
}

int	init_wall_assets(t_data *data)
{
	int	i;
	int	width;
	int	height;
	int	ret;

	i = 0;
	ret = 0;
	while (i < 4 && ret == 0)
	{
		data->wall_assets[i] = mlx_new_image_from_file(data->mlx,
				data->texture[i].path, &width, &height);
		if (data->wall_assets[i] == MLX_NULL_HANDLE)
			ret = -ERROR_LOAD_ASSET;
		if (width != WALL_SIZE || height != WALL_SIZE)
			ret = -ERROR_IMG_SIZE;
		i++;
	}
	if (ret < 0)
		destroy_wall_assets(data, i);
	return (ret);
}

int	init_game(t_data *data)
{
	int	ret;

	ret = init_player(data);
	if (ret < 0)
		return (ret);
	ret = init_door(data);
	if (ret < 0)
	{
		free_map(data);
		free_texture_paths(data);
		return (ret);
	}
	data->frame = mlx_new_image(data->mlx, data->win_infos.width,
			data->win_infos.height);
	if (data->frame == MLX_NULL_HANDLE)
		return (-ERROR_LOAD_ASSET);
	data->mini_map = mlx_new_image(data->mlx, 176, 176);
	if (data->mini_map == MLX_NULL_HANDLE)
		return (-ERROR_LOAD_ASSET);
	data->keys = (t_keys){0};
	data->keys.e_lock = false;
	data->floor_color = rgb_to_color(data->plans_color[1], 100);
	data->ceil_color = rgb_to_color(data->plans_color[0], 100);
	data->map->doors = set_doors_map(data);
	if (!data->map->doors)
		return (-ERROR_MALLOC);
	return (NO_ERROR);
}
