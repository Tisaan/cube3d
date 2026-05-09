/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 16:40:50 by tseche            #+#    #+#             */
/*   Updated: 2026/05/09 10:18:32 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/parsing.h"
#include "../includes/debug.h"
#include "../includes/utils.h"
#include "../includes/player.h"
#include <sys/wait.h>
#include <unistd.h>

static bool	init_window(mlx_context mlx, mlx_window *win, t_win_infos *infos)
{
	infos->title = "cub3D";
	infos->width = 1280;
	infos->height = 720;
	infos->is_fullscreen = false;
	infos->is_resizable = false;
	*win = mlx_new_window(mlx, infos);
	if (*win == MLX_NULL_HANDLE)
		return (false);
	return (true);
}

// void	render(void *param)
// {
// 	t_data	*data;
//
// 	data = (t_data *)param;
// 	render_2D_map(data);
// }

static int	process(t_data *data)
{
	int			ret;

	ret = init_player(data);
	if (ret < 0)
		return (ret);
	display_player_data(data->player);
	render_2D_map(data);
	mlx_on_event(data->mlx, data->win, MLX_KEYDOWN, key_hooks, data);
	mlx_on_event(data->mlx, data->win, MLX_WINDOW_EVENT, window_hook, data);
	mlx_add_loop_hook(data->mlx, render_player, data);
	mlx_loop(data->mlx);
	return (NO_ERROR);
}

static void	set_img_pixel(t_data *data, mlx_image img)
{
	int			x;
	int			y;
	mlx_color	color;

	color.rgba = 0xFFFFFFFF;
	y = 0;
	while (y < WALL_SIZE - 1)
	{
		x = 0;
		while (x < WALL_SIZE - 1)
		{
			mlx_set_image_pixel(data->mlx, img, x, y, color);
			x++;
		}
		y++;
	}
}

int	main(int ac, char **av)
{
	t_data	data;
	int		ret;

	if (ac != 2)
	{
		ft_print_error("Invalid number of arguments.\n");
		return (1);
	}
	data = parse(av[1]);
	if (data.map == NULL)
		return (1);
	display_map_data(data);
	data.mlx = mlx_init();
	data.win_infos = (t_win_infos){0};
	if (!init_window(data.mlx, &data.win, &data.win_infos))
	{
		free_all(&data, -1);
		mlx_destroy_context(data.mlx);
		return (1);
	}
	data.wall_assets[0] = mlx_new_image(data.mlx, WALL_SIZE, WALL_SIZE);
	if (data.wall_assets[0] == MLX_NULL_HANDLE)
		return (-ERROR_LOAD_ASSET);
	set_img_pixel(&data, data.wall_assets[0]);
	ret = process(&data);
	if (ret < 0)
		throw_error(ret);
	clean_exit(&data);
	return (ret < 0);
}
