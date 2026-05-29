/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 16:40:50 by tseche            #+#    #+#             */
/*   Updated: 2026/05/29 15:07:29 by pcaplat          ###   ########.fr       */
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

static int	ready(t_data *data)
{
	int	ret;

	data->mlx = mlx_init();
	data->win_infos = (t_win_infos){0};
	if (!init_window(data->mlx, &data->win, &data->win_infos))
	{
		free_all(data, -1);
		mlx_destroy_context(data->mlx);
		return (1);
	}
	ret = init_game(data);
	if (ret < 0)
	{
		throw_error(ret);
		return (1);
	}
	return (ret);
}

static int	process(t_data *data)
{
	mlx_on_event(data->mlx, data->win, MLX_KEYDOWN, key_hooks, data);
	mlx_on_event(data->mlx, data->win, MLX_KEYUP, key_up_hook, data);
	mlx_on_event(data->mlx, data->win, MLX_WINDOW_EVENT, window_hook, data);
	mlx_add_loop_hook(data->mlx, time_update, data);
	mlx_add_loop_hook(data->mlx, update_player_pos, data);
	mlx_add_loop_hook(data->mlx, update_player_rot, data);
	mlx_add_loop_hook(data->mlx, ray_hook, data);
	mlx_add_loop_hook(data->mlx, render, data);
	start_timer(&data->timer);
	mlx_loop(data->mlx);
	return (NO_ERROR);
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
	data = (t_data){0};
	data = parse(av[1]);
	if (data.map == NULL)
		return (1);
	ret = ready(&data);
	if (ret < 0)
		return (ret);
	ret = process(&data);
	if (ret < 0)
		throw_error(ret);
	clean_exit(&data);
	return (ret < 0);
}
