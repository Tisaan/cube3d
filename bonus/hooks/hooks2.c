/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: von <von@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 15:54:55 by tseche            #+#    #+#             */
/*   Updated: 2026/06/10 12:53:26 by von              ###   ########.fr       */
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

static char	*set_prompt(char *prefix, char *postfix, bool free_postfix)
{
	char	*tmp;
	int		len;
	int		i;
	int		j;

	len = ft_strlen(postfix);
	len += ft_strlen(prefix);
	tmp = malloc(sizeof(char) * (len + 1));
	if (!tmp)
	{
		if (free_postfix)
			free(postfix);
		return (NULL);
	}
	i = 0;
	j = 0;
	while (prefix[i] && j < len)
		tmp[j++] = prefix[i++];
	i = 0;
	while (postfix[i] && j < len)
		tmp[j++] = postfix[i++];
	if (free_postfix)
		free(postfix);
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
	fps = set_prompt("FPS: ", fps, true);
	if (fps == NULL)
		return ;
	mlx_string_put(data->mlx, data->win, 15 + FONT_SIZE, 15 + FONT_SIZE, color, fps);
	free(fps);
	fps = set_prompt("SEED: ", data->seed, false);
	if (!fps)
		return ;
	mlx_string_put(data->mlx, data->win, 15 + FONT_SIZE, 45 + FONT_SIZE, color, fps);
	free(fps);
}
