/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 16:40:50 by tseche            #+#    #+#             */
/*   Updated: 2026/06/15 14:21:07 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"
#include "includes/parsing.h"
#include "includes/debug.h"
#include "includes/utils.h"
#include "includes/player.h"
#include "includes/bonus.h"
#include <sys/wait.h>
#include <unistd.h>

void	toogle_door_state(void *param)
{
	t_data	*data;
	int		px;
	int		py;

	data = (t_data *)param;
	px = (int)(data->player->pos.x / WALL_SIZE + data->player->dir.x);
	py = (int)(data->player->pos.y / WALL_SIZE+ data->player->dir.y);
	if (py < 0 || py >= data->map->height || px < 0 || px >= data->map->width)
		return ;
	if (data->keys.e && !data->keys.e_lock)
	{
		if (data->map->doors[py][px] == ' ')
			return ;
		else if (data->map->doors[py][px] == '1')
			data->map->doors[py][px] = '0';
		else
		{
			data->player->pos.x -= data->player->dir.x * WALL_SIZE * 0.1f;
			data->player->pos.y -= data->player->dir.y * WALL_SIZE * 0.1f;
			data->map->doors[py][px] = '1';
		}
		data->keys.e_lock = true;
	}
}

static int	ready(t_data *data)
{
	int	ret;

	data->mlx = mlx_init();
	data->win_infos = (t_win_infos){0};
	ret = init_wall_assets(data);
	if (ret < 0)
	{
		free_map(data);
		free_texture_paths(data);
		return (ret);
	}
	if (!init_window(data->mlx, &data->win, &data->win_infos))
	{
		free_map(data);
		free_texture_paths(data);
		mlx_destroy_context(data->mlx);
		return (1);
	}
	ret = init_game(data);
	if (ret < 0)
	{
		throw_error(ret);
		return (ret);
	}
	return (ret);
}

static int	process(t_data *data)
{
	mlx_on_event(data->mlx, data->win, MLX_KEYDOWN, key_hooks, data);
	mlx_on_event(data->mlx, data->win, MLX_KEYUP, key_up_hook, data);
	mlx_on_event(data->mlx, data->win, MLX_WINDOW_EVENT, window_hook, data);
	mlx_on_event(data->mlx, data->win, MLX_MOUSEDOWN, handle_mouse_clic, data);
	mlx_add_loop_hook(data->mlx, time_update, data);
	mlx_add_loop_hook(data->mlx, (void (*)(void *))update_mouse_rot, data);
	mlx_add_loop_hook(data->mlx, update_player_pos, data);
	mlx_add_loop_hook(data->mlx, update_player_rot, data);
	mlx_add_loop_hook(data->mlx, update_mini_map, data);
	mlx_add_loop_hook(data->mlx, toogle_door_state, data);
	mlx_add_loop_hook(data->mlx, ray_hook, data);
	mlx_add_loop_hook(data->mlx, render, data);
	mlx_add_loop_hook(data->mlx, display_game_infos, data);
	start_timer(&data->timer);
	mlx_loop(data->mlx);
	return (NO_ERROR);
}

static int	handle_seed_args(t_data **data, int ac, char **av, long int *seed)
{
	if (ac == 3 && ft_strncmp(av[1], "seed\0", 5) == 0)
	{
		if (ft_strlen(av[2]) == (size_t)skip_digits(av[2])
			&& ft_strlen(av[2]) == 12)
		{
			*seed = ft_atol(av[2]);
			if (*seed < 0 || !check_seed(*seed))
			{
				throw_error_bonus(SEED_INVALID);
				return (1);
			}
			*data = main_proc(*seed);
			if (!data || !*data)
				return (1);
			return (set_default(*data));
		}
		else
		{
			throw_error_bonus(SEED_INVALID);
			return (1);
		}
	}
	return (0);
}

static int	switch_gen(t_data **data, int ac, char **av, long int *seed)
{
	if (ac == 2 && ft_strncmp(av[1], "seed\0", 5) == 0)
	{
		*seed = gen_seed();
		*data = main_proc(*seed);
		if (!data || !*data)
			return (1);
		return (set_default(*data));
	}
	else if (ac == 2)
	{
		*data = ft_calloc(sizeof(t_data), 1);
		if (!data || !*data)
		{
			throw_error(ERROR_MALLOC);
			return (1);
		}
		parse(av[1], *data);
	}
	else
	{
		ft_print_error("Error:\nInvalid number of arguments.\n");
		return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data		*data;
	int			ret;
	long int	seed;

	data = NULL;
	if (handle_seed_args(&data, ac, av, &seed) != 0)
		return (1);
	else if (switch_gen(&data, ac, av, &seed) != 0)
		return (1);
	if (data->map == NULL)
		return (1);
	ret = ready(data);
	if (ret < 0)
		return (ret);
	ret = process(data);
	if (ret < 0)
		throw_error(ret);
	if (ret == -ERROR_LOAD_ASSET)
		clean_exit(data, false);
	else
		clean_exit(data, true);
	return (ret < 0);
}
