/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 16:40:50 by tseche            #+#    #+#             */
/*   Updated: 2026/04/29 18:56:49 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/parsing.h"
#include <sys/wait.h>
#include <unistd.h>

static void	ft_print_error(const char *msg)
{
	write(2, msg, ft_strlen(msg));
}

static void	draw_square(mlx_window win, mlx_context mlx, int x, int y, int size, mlx_color color)
{
	int	old_x;

	old_x = x;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			mlx_pixel_put(mlx, win, x++, y, color);
		y++;
		x = old_x;
	}
}

static bool	init_window(mlx_context mlx, mlx_window *win, t_win_infos *win_infos)
{
	win_infos->title = "cub3D";
	win_infos->width = 1920;
	win_infos->height = 1080;
	*win = mlx_new_window(mlx, win_infos);
	if (win == MLX_NULL_HANDLE)
		return (false);
	return (true);
}

int	main(int ac, char **av)
{
	mlx_color	color;
	t_data	data;

	if (ac != 2)
	{
		ft_print_error("Invalid number of arguments.\n");
		return (1);
	}
	data = parse(av[1]);
	if (data.map == NULL)
		return (1);
	printf("%d: %s\n", data.texture[0].dir, data.texture[0].path);
	printf("%d: %s\n", data.texture[1].dir, data.texture[1].path);
	printf("%d: %s\n", data.texture[2].dir, data.texture[2].path);
	printf("%d: %s\n", data.texture[3].dir, data.texture[3].path);
	data.mlx = mlx_init();
	data.win_infos = (t_win_infos){0};
	if (!init_window(data.mlx, &data.win, &data.win_infos))
	{
		mlx_destroy_context(data.mlx);
		return (1);
	}
	color.rgba = 0x00FF00FF;
	draw_square(data.win, data.mlx, 500, 500, 500, color);
	mlx_loop(data.mlx);
	mlx_destroy_window(data.mlx, data.win);
	mlx_destroy_context(data.mlx);
	return (0);
}
