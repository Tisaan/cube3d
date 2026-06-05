/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 13:07:01 by pcaplat           #+#    #+#             */
/*   Updated: 2026/06/03 21:00:22 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/debug.h"
#include <stdlib.h>
#include <unistd.h>

static char	*dup_str_chunk(char *str, int start, int size)
{
	static bool	display = true;
	char	*chunk;
	int		offset;
	int		len;
	int		i;
	int		j;

	chunk = malloc(sizeof(char) * size + 1);
	if (!chunk)
		return (NULL);
	// if (display)
	// {
	// 	printf("str: %s, len: %d, start: %d, size: %d\n", str, (int)ft_strlen(str), start, size);
	// }
	if (start < 0)
		start = 0;
	offset = 0;
	len = (int)ft_strlen(str);
	if (len < size)
		offset = (size - len) / 2;
	i = 0;
	while (i < offset)
		chunk[i++] = ' ';
	j = start;
	while (i < size)
	{
		if (str[j])
			chunk[i] = str[j++];
		else
		 	chunk[i] = ' ';
		i++;
	}
	chunk[i] = '\0';
	display = false;
	return (chunk);
}

static char	*set_space_section(int size)
{
	// static bool	display = true;
	char	*section;
	int		i;

	section = malloc(sizeof(char) * size + 1);
	if (!section)
		return (NULL);
	i = 0;
	while (i < size)
		section[i++] = ' ';
	section[i] = '\0';
	// if (display)
	// {
	// 	write(1, "section: |", 10);
	// 	write(1, section, ft_strlen(section));
	// 	write(1, "|\n", 2);
	// }
	return (section);
}


char	**set_viewport(t_map *map, t_player *p, int size)
{	
	char	**viewport;
	int		viewport_y;
	int		j;
	int		offset;

	viewport = malloc(sizeof(char *) * size + 1);
	if (!viewport)
		return (NULL);
	offset = (size - map->height) / 2;
	if (offset < 0)
		offset = 0;
	viewport_y = (int)(p->pos.y / WALL_SIZE) - offset;
	j = 0;
	while(viewport_y < 0 || (j < offset && map->height < size))
	{
		viewport[j] = set_space_section(size);
		if (!viewport[j])
		{
			ft_freeptr((void **)viewport);
			return (NULL);
		}
		j++;
		if (viewport_y < 0)
			viewport_y++;
	}
	while (j < size)
	{
		if (map->grid[viewport_y])
			viewport[j] = dup_str_chunk(map->grid[viewport_y], p->pos.x / WALL_SIZE - offset, size);
		else
			viewport[j] = set_space_section(size);
		if (!viewport[j])
		{
			ft_freeptr((void **)viewport);
			return (NULL);
		}
		j++;
		if (map->grid[viewport_y])
			viewport_y++;
	}
	viewport[j] = NULL;
	return (viewport);
}

int	set_mini_map_pixels(t_data *data)
{
	static bool	display = true;
	int		wall_size;
	// int		player_size;
	char	**viewport;

	wall_size = MINI_MAP_SIZE / 10;
	// player_size = wall_size / 2;
	place_player(data, data->map->grid);
	viewport = set_viewport(data->map, data->player, wall_size);
	if (!viewport)
	{
		printf("NULL\n");
		return (-ERROR_MALLOC);
	}
	data->map->grid[(int)data->player->pos.y / WALL_SIZE][(int)data->player->pos.x / WALL_SIZE] = '0';
	if (display)
	{
		display = false;
	}
	system("clear");
	display_viewport(viewport);
	printf("player.pos(%d, %d)\n", (int)data->player->pos.x / WALL_SIZE, (int)data->player->pos.y / WALL_SIZE);
	return (NO_ERROR);
}
