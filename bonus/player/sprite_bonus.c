/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat </var/spool/mail/pcaplat>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 10:18:18 by pcaplat           #+#    #+#             */
/*   Updated: 2026/06/12 13:16:06 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/player.h"
#include "../includes/cub3d.h"

static void	clear_spritesheet(t_data *data, mlx_image **spritesheet, int i)
{
	while (i >= 0)
	{
		mlx_destroy_image(data->mlx, *spritesheet[i]);
		i--;
	}
	free(*spritesheet);
}

static char	*add_path_extension(char *file_path, char *name, char *extension)
{
	char	*tmp;
	char	*path;

	tmp = ft_strjoin(file_path, name);
	if (!tmp)
		return (NULL);
	path = ft_strjoin(tmp, extension);
	free (tmp);
	return (path);
}

static char	*build_path(int i)
{
	char	*tmp;
	char	*path;
	char	*frame_nb;

	tmp = ft_strjoin(SPRITE_PATH, SPRITE_NAME);
	if (!tmp)
		return (NULL);
	frame_nb = ft_itoa(i + 1);
	if (!frame_nb)
	{
		free(tmp);
		return (NULL);
	}
	path = add_path_extension(tmp, frame_nb, ".png");
	free(tmp);
	free(frame_nb);
	return (path);
}

static int	fill_spritesheet(t_data *d, t_animated_sprite_2d *s)
{
	int		i;
	char	*path;

	i = 0;
	while (i < SPRITE_FRAMES)
	{
		path = build_path(i);
		if (!path)
		{
			clear_spritesheet(d, &s->spritesheet, i - 1);
			return (-ERROR_MALLOC);
		}
		s->spritesheet[i] =
			mlx_new_image_from_file(d->mlx, path, &s->width, &s->height);
		if (!s->spritesheet[i])
		{
			clear_spritesheet(d, &s->spritesheet, i - 1);
			free(path);
			return (-ERROR_PATH_TEXTURE);
		}
		free(path);
		i++;
	}
	return (NO_ERROR);
}

int	init_player_sprite(t_data *data)
{
	t_player	*player;
	int			ret;

	player = data->player;
	player->sprite.spritesheet = malloc(sizeof(mlx_image) * SPRITE_FRAMES);
	if (!player->sprite.spritesheet)
		return (-ERROR_MALLOC);
	ret = fill_spritesheet(data, &player->sprite);
	if (ret < 0)
		return (-ERROR_PATH_TEXTURE);
	return (NO_ERROR);
}
