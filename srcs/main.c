/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 16:40:50 by tseche            #+#    #+#             */
/*   Updated: 2026/05/04 17:36:56 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/parsing.h"
#include <sys/wait.h>
#include <unistd.h>

void	display_map_data(t_data data)
{
	printf("%d: <%s>\n", data.texture[0].dir, data.texture[0].path);
	printf("%d: <%s>\n", data.texture[1].dir, data.texture[1].path);
	printf("%d: <%s>\n", data.texture[2].dir, data.texture[2].path);
	printf("%d: <%s>\n", data.texture[3].dir, data.texture[3].path);
	printf("Ceiling color: (%d, %d, %d)\tFloor color: (%d, %d, %d)\n", data.plans_color[CEILING - 5].rgb[0],data.plans_color[CEILING - 5].rgb[1],data.plans_color[CEILING - 5].rgb[2],
		data.plans_color[FLOOR - 5].rgb[0],data.plans_color[FLOOR - 5].rgb[1],data.plans_color[FLOOR - 5].rgb[2]);
}

// static void	ft_print_error(const char *msg)
// {
// 	write(2, msg, ft_strlen(msg));
// }

static bool	init_window(mlx_context mlx, mlx_window *win, t_win_infos *win_infos)
{
	win_infos->title = "cub3D";
	win_infos->width = 1280;
	win_infos->height = 720;
	win_infos->is_fullscreen = false;
	win_infos->is_resizable = false;
	*win = mlx_new_window(mlx, win_infos);
	if (*win == MLX_NULL_HANDLE)
		return (false);
	return (true);
}

static void	init_pip_boy(t_img *img, t_data *data)
{
	img->asset = mlx_new_image_from_file(data->mlx, "assets/pip_boy.png", &img->width, &img->height);
	img->data = data;
}

static void	draw(t_img *img)
{
	mlx_color	color;
	float		scale_width;
	float		scale_height;


	printf("Function called\n");
	color.rgba = 0xF000000;
	mlx_clear_window(img->data->mlx, img->data->win, color);
	scale_width = (float)img->data->win_infos.width / (float)img->width;
	scale_height = (float)img->data->win_infos.height / (float)img->height;
	mlx_put_transformed_image_to_window(img->data->mlx, img->data->win, img->asset, 0, 0, scale_width * 1.0f, scale_height * 1.0f, 0.0f);
}

static void	key_hooks(int key, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (key == Q_KEY || key == ESC_KEY)
		mlx_loop_end(data->mlx);
	else if (key == F_KEY)
	{
		if (data->win_infos.is_fullscreen == false)
		{
			data->win_infos.is_fullscreen = true;
			mlx_set_window_fullscreen(data->mlx, data->win, true);
		}
		else
		{
			data->win_infos.is_fullscreen = false;
			mlx_restore_window(data->mlx, data->win);
			mlx_set_window_fullscreen(data->mlx, data->win, false);
		}
	}
}

static void	window_hook(int event, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (event == WIN_CLOSE)
		mlx_loop_end(data->mlx);
}

int	main(int ac, char **av)
{
	t_img	pip_boy;
	t_data	data;

	(void)av;
	(void)ac;
	// if (ac != 2)
	// {
	// 	ft_print_error("Invalid number of arguments.\n");
	// 	return (1);
	// }
	//data = parse(av[1]);
	// if (data.map == NULL)
	// 	return (1);
	// display_map_data(data);
	data.mlx = mlx_init();
	data.win_infos = (t_win_infos){0};
	if (!init_window(data.mlx, &data.win, &data.win_infos))
	{
		free_all(&data);
		mlx_destroy_context(data.mlx);
		return (1);
	}
	init_pip_boy(&pip_boy, &data);
	draw(&pip_boy);
	mlx_on_event(data.mlx, data.win, MLX_KEYDOWN, key_hooks, &data);
	mlx_on_event(data.mlx, data.win, MLX_WINDOW_EVENT, window_hook, &data);

	mlx_loop(data.mlx);

	mlx_destroy_image(data.mlx, pip_boy.asset);
	mlx_destroy_window(data.mlx, data.win);
	mlx_destroy_context(data.mlx);
	return (0);
}
