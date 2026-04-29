/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 16:40:50 by tseche            #+#    #+#             */
/*   Updated: 2026/04/29 14:51:31 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
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
	mlx_context	mlx;
	t_win_infos	win_infos;
	mlx_window	win;

	if (ac != 2)
	{
		ft_print_error("Invalid number of arguments.\n");
		return (1);
	}
	(void)av;
	mlx = mlx_init();
	win_infos = (t_win_infos){0};
	if (!init_window(mlx, &win, &win_infos))
	{
		mlx_destroy_context(mlx);
		return (1);
	}
	color.rgba = 0x00FF00FF;
	draw_square(win, mlx, 500, 500, 500, color);
	mlx_loop(mlx);
	mlx_destroy_window(mlx, win);
	mlx_destroy_context(mlx);
	return (0);
}
