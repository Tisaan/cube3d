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

static char	*dup_str_section(char *str, int start, int end)
{
	static bool	display = true;
	char	*section;
	int		size;
	int		i;
	int		j;
	int		offset;

	size = end - start + 1;
	offset = 0;
	if (display)
	{
		printf("end: %d, start: %d, size: %d, str: %s\n", end, start, size, str);
		display = false;
	}
	section = malloc(sizeof(char) * size + 1);
	if (!section)
		return (NULL);
	i = 0;
	if ((int)ft_strlen(str) < size)
		offset = (size - ft_strlen(str)) / 2;
	while (i < offset)
		section[i++] = ' ';
	j = 0;
	while (str[j])
		section[i++] = str[j++];
	while (i < size)
		section[i++] = ' ';
	section[i] = '\0';
	return (section);
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
	static bool	display = true;
	char	**viewport;
	int		viewport_y;
	int		j;
	int		offset;

	viewport = malloc(sizeof(char *) * size + 1);
	if (!viewport)
		return (NULL);
	offset = size / 2;
	if (map->height < size)
	{
		if (display)
			printf("hello\n");
		offset = (size - map->height) / 2;
	}
	viewport_y = (int)(p->pos.y / WALL_SIZE) - offset;
	j = 0;
	if (display)
	{
		printf("size: %d, offset: %d\n", size, offset);
		printf("map height: %d\n", map->height);
		printf("=====VIEWPORT=====\n");
	}
	while(viewport_y < 0 || (j < offset && map->height < size))
	{
		viewport[j] = set_space_section(size);
		if (!viewport[j])
		{
			ft_freeptr((void **)viewport);
			return (NULL);
		}
		if (display)
		{
			printf("viewp[%d]: <%s>\n", j, viewport[j]);
		}
		j++;
		if (viewport_y < 0)
			viewport_y++;
	}
	// while (j < offset)
	// {
	// 	viewport[j] = dup_str_section(map->grid[viewport_y], p->pos.x / WALL_SIZE - offset, p->pos.x / WALL_SIZE + offset);
	// 	if (!viewport[j])
	// 	{
	// 		ft_freeptr((void **)viewport);
	// 		return (NULL);
	// 	}
	// 	if (display)
	// 	{
	// 		printf("viewp[%d]: <%s>\n", j, viewport[j]);
	// 	}
	// 	j++;
	// 	viewport_y++;
	// }
	while (j < size)
	{
		if (map->grid[viewport_y])
			viewport[j] = dup_str_section(map->grid[viewport_y], p->pos.x / WALL_SIZE - offset, p->pos.x / WALL_SIZE + offset);
		else
			viewport[j] = set_space_section(size);
		if (!viewport[j])
		{
			ft_freeptr((void **)viewport);
			return (NULL);
		}
		if (display)
		{
			printf("viewp[%d]: <%s>\n", j, viewport[j]);
		}
		j++;
		if (map->grid[viewport_y])
			viewport_y++;
	}
	if (display)
		printf("\n");
	display = false;
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
	viewport = set_viewport(data->map, data->player, wall_size);
	if (!viewport)
	{
		printf("NULL\n");
		return (-ERROR_MALLOC);
	}
	if (display)
	{
		printf("player.pos(%d, %d)\n", (int)data->player->pos.x / WALL_SIZE, (int)data->player->pos.y / WALL_SIZE);
		display = false;
	}
	// display_viewport(viewport);
	return (NO_ERROR);
}
