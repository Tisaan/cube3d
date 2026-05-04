/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 16:40:50 by tseche            #+#    #+#             */
/*   Updated: 2026/05/04 14:56:51 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/parsing.h"
#include <sys/wait.h>
#include <unistd.h>

typedef enum	e_key_code
{
	Q_KEY = 20,
	ESC_KEY = 41,
}	t_key_code;

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
	win_infos->is_resizable = true;
	*win = mlx_new_window(mlx, win_infos);
	if (win == MLX_NULL_HANDLE)
		return (false);
	return (true);
}

void	key_hooks(int key, void *param)
{
	if (key == Q_KEY || key == ESC_KEY)
		mlx_loop_end((mlx_context)param);
	printf("keycode: %d\n", key);
}

void	window_hook(int event, void *param)
{
	if (event == 0)
		mlx_loop_end((mlx_context)param);
}

int	main(int ac, char **av)
{
	mlx_image	pip_boy;
	t_data	data;
	int		width;
	int		height;

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
	pip_boy = mlx_new_image_from_file(data.mlx, "assets/pip_boy.png", &width, &height);
	// put pip_boy img with half width, and height and without touching the sprite rotation
	mlx_put_transformed_image_to_window(data.mlx, data.win, pip_boy, 0, 0, 0.5f, 0.5f, 0.0f);
	mlx_on_event(data.mlx, data.win, MLX_KEYDOWN, key_hooks, data.mlx);
	mlx_on_event(data.mlx, data.win, MLX_WINDOW_EVENT, window_hook, data.mlx);

	mlx_loop(data.mlx);

	mlx_destroy_image(data.mlx, pip_boy);
	mlx_destroy_window(data.mlx, data.win);
	mlx_destroy_context(data.mlx);
	return (0);
}
