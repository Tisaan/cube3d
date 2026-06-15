/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 16:52:40 by tseche            #+#    #+#             */
/*   Updated: 2026/06/15 15:15:28 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

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
	return (ret);
}

int	init_mouse(t_data *d)
{
	t_vect	*v;

	v = malloc(sizeof(t_vect));
	if (!v)
		return (-ERROR_MALLOC);
	set_vect(v, WIN_HEIGHT / 2, WIN_WIDTH / 2);
	d->mouse_pos = v;
	mlx_mouse_hide(d->mlx);
	return (NO_ERROR);
}
