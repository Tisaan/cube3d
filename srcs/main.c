/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 16:40:50 by tseche            #+#    #+#             */
/*   Updated: 2026/04/29 12:05:50 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	ft_print_error(const char *msg)
{
	write(2, msg, ft_strlen(msg));
}

int	main(int ac, char **av)
{
	mlx_context				mlx;
	mlx_window_create_info	win_infos;
	mlx_window				win;

	if (ac != 2)
	{
		ft_print_error("Invalid number of arguments.\n");
		return (1);
	}
	(void)av;
	printf("Hello there!\n");
	win_infos = (mlx_window_create_info){0};
	win_infos.title = "cub3D";
	win_infos.width = 400;
	win_infos.height = 400;
	mlx = mlx_init();
	win = mlx_new_window(mlx, &win_infos);

	mlx_destroy_window(mlx, win);
	mlx_destroy_context(mlx);
	return (0);
}
