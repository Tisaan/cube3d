/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 16:52:40 by tseche            #+#    #+#             */
/*   Updated: 2026/06/09 15:16:19 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	set_map_door(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map->height)
	{
		j = 0;
		while (j < data->map->width)
		{
			if (data->map->grid[i][j] == 'D')
				data->map_door[i][j] = close_state;
			else
				data->map_door[i][j] = not_door_state;
			j++;
		}
		i++;
	}
}

int	init_map_door(t_data *data)
{
	int	i;
	int	j;

	data->map_door = ft_calloc(data->map->height + 1, sizeof(t_state_obj *));
	if (!data->map_door)
		return (-ERROR_MALLOC);
	i = 0;
	while (i < data->map->height)
	{
		data->map_door[i] = ft_calloc(data->map->width + 1,
				sizeof(t_state_obj));
		if (!data->map_door[i])
		{
			ft_freeptr((void **)data->map_door);
			return (-ERROR_MALLOC);
		}
		i++;
	}
	set_map_door(data);
	return (0);
}

int	init_door(t_data *data)
{
	int	width;
	int	height;
	int	ret;

	data->door_asset[0] = mlx_new_image_from_file(data->mlx, DOOR_ASSET_CLOSE,
			&width, &height);
	data->door_asset[1] = mlx_new_image_from_file(data->mlx, DOOR_ASSET_OPEN,
			&width, &height);
	ret = 0;
	if (data->door_asset[0] == MLX_NULL_HANDLE
		|| data->door_asset[1] == MLX_NULL_HANDLE)
		ret = -ERROR_LOAD_ASSET;
	if (width != WALL_SIZE || height != WALL_SIZE)
		ret = -ERROR_IMG_SIZE;
	if (ret < 0)
	{
		mlx_destroy_image(data->mlx, data->door_asset[0]);
		mlx_destroy_image(data->mlx, data->door_asset[1]);
		return (ret);
	}
	ret = init_map_door(data);
	return (ret);
}
