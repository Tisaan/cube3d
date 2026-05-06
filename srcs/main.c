/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 16:40:50 by tseche            #+#    #+#             */
/*   Updated: 2026/05/06 20:01:50 by pcaplat          ###   ########.fr       */
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

// static void	draw(t_img *img)
// {
// 	mlx_color	color;
// 	float		scale_width;
// 	float		scale_height;
//
// 	printf("Function called\n");
// 	color.rgba = 0xF000000;
// 	mlx_clear_window(img->data->mlx, img->data->win, color);
// 	scale_width = (float)img->data->win_infos.width / (float)img->width;
// 	scale_height = (float)img->data->win_infos.height / (float)img->height;
// 	mlx_put_transformed_image_to_window(img->data->mlx, img->data->win,
// 		img->asset, 0, 0, scale_width * 1.0f, scale_height * 1.0f, 0.0f);
// }

void	render(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	render_2D_map(data);
}

static int	process(t_data *data)
{
	t_img		pip_boy;
	int			ret;

	ret = init_player(data);
	if (ret < 0)
		return (ret);
	display_player_data(data->player);
	init_pip_boy(&pip_boy, data);
	mlx_on_event(data->mlx, data->win, MLX_KEYDOWN, key_hooks, data);
	mlx_on_event(data->mlx, data->win, MLX_WINDOW_EVENT, window_hook, data);
	mlx_add_loop_hook(data->mlx, render, data);
	mlx_loop(data->mlx);
	mlx_destroy_image(data->mlx, pip_boy.asset);
	mlx_destroy_image(data->mlx, data->wall_asset);
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
	data = parse(av[1]);
	if (data.map == NULL)
		return (1);
	display_map_data(data);
	free_all(&data, -1);
	return 1;
	data.mlx = mlx_init();
	data.win_infos = (t_win_infos){0};
	if (!init_window(data.mlx, &data.win, &data.win_infos))
	{
		free_all(&data, -1);
		mlx_destroy_context(data.mlx);
		return (1);
	}
	ret = process(&data);
	if (ret < 0)
		throw_error(ret);
	clean_exit(&data);
	return (ret < 0);
}
