/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 15:54:55 by tseche            #+#    #+#             */
/*   Updated: 2026/06/10 08:45:02 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	update_mouse_rot(t_data *d)
{
	int	x;
	int	y;

	mlx_mouse_get_pos(d->mlx, &x, &y);
	if (x != (int)d->mouse_pos->x)
	{
		if (x > d->mouse_pos->x)
		{
			rotate_vect(&d->player->dir, d->delta * PLAYER_ROT_SPEED);
			rotate_vect(&d->player->camera, d->delta * PLAYER_ROT_SPEED);
		}
		else
		{
			rotate_vect(&d->player->dir, -(d->delta * PLAYER_ROT_SPEED));
			rotate_vect(&d->player->camera, -(d->delta * PLAYER_ROT_SPEED));
		}
		mlx_mouse_move(d->mlx, d->win, WIN_HEIGHT / 2, WIN_WIDTH / 2);
	}
}

static char	*set_fps_prompt(char *fps, char *prompt)
{
	char	*tmp;
	int		len;
	int		i;
	int		j;

	len = ft_strlen(fps) + ft_strlen(prompt);
	tmp = malloc(sizeof(char) * len + 1);
	if (!tmp)
	{
		free(fps);
		return (NULL);
	}
	i = 0;
	j = 0;
	while (prompt[i] && j < len)
		tmp[j++] = prompt[i++];
	i = 0;
	while (fps[i] && j < len)
		tmp[j++] = fps[i];
	free(fps);
	tmp[j] = '\0';
	return (tmp);
}

void	display_game_infos(void *param)
{
	t_data		*data;
	mlx_color	color;
	char		*fps;

	data = (t_data *)param;
	if (data->keys.f3 == false)
		return ;
	color.rgba = 0xFFFFFFFF;
	fps = ft_itoa(data->timer.fps);
	if (!fps)
	{
		throw_error(-ERROR_MALLOC);
		return ;
	}
	fps = set_fps_prompt(fps, "FPS: ");
	if (fps == NULL)
		return ;
	mlx_string_put(data->mlx, data->win, 10 + FONT_SIZE, 10 + FONT_SIZE, color, fps);
	free(fps);
}
