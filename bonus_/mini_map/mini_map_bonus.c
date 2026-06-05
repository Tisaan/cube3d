/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 14:29:30 by pcaplat           #+#    #+#             */
/*   Updated: 2026/06/05 16:21:01 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/bonus.h"

static char	*dup_viewport_line(t_player *p, t_map *map, int map_x, int map_y)
{
	char	*line;
	int		i;

	line = malloc(sizeof(char) * (11 + 1));
	if (!line)
		return (NULL);
	i = 0;
	while(map_x < 0 && i < 11)
	{
		line[i++] = ' ';
		map_x++;
	}
	while (map->grid[map_y][map_x] && i < 11)
	{
		if (map_y == (int)p->pos.y / WALL_SIZE && map_x == (int)p->pos.x / WALL_SIZE)
			line[i] = 'P';
		else
			line[i] = map->grid[map_y][map_x];
		i++;
		map_x++;
	}
	while (i < 11)
		line[i++] = ' ';
	line[i] = '\0';
	return (line); 
}

static void	clear_viewport(t_map *map, int i)
{
	while (i >= 0)
		free(map->viewport[--i]);
	free(map->viewport);
}

int	fill_viewport(t_player *player, t_map *map, t_point view)
{
	static bool	display = true;
	int	map_y;
	int	i;

	map_y = view.y;
	i = 0;
	while (map_y < 0)
	{
		map->viewport[i] = ft_strdup("           ");
		if (!map->viewport[i])
		{
			clear_viewport(map, i);
			return (-ERROR_MALLOC);
		}
		i++;
		map_y++;
	}
	while (map->grid[map_y] && i < 11)
	{
		map->viewport[i] = dup_viewport_line (player, map, view.x, map_y);
		if (!map->viewport[i])
		{
			clear_viewport(map, i);
			return (-ERROR_MALLOC);
		}
		map_y++;
		i++;
	}
	while (i < 11)
	{
		map->viewport[i] = ft_strdup("           ");
		if (!map->viewport[i])
		{
			clear_viewport(map, i);
			return (-ERROR_MALLOC);
		}
		i++;
	}
	if (display)
		printf("i: %d\n", i);
	display = false;
	map->viewport[i] = NULL;
	return (NO_ERROR);
}

int	set_viewport(t_player *player, t_map *map)
{
	static bool	display = true;
	t_point	view_pos;

	map->viewport = malloc(sizeof(char *) * (11 + 1));
	if (!map->viewport)
		return (-ERROR_MALLOC);
	view_pos.x = (int)(player->pos.x / WALL_SIZE) - 5;
	view_pos.y = (int)(player->pos.y / WALL_SIZE) - 5;
	if (display)
		printf("view(%d, %d)\n", view_pos.x, view_pos.y);
	if (fill_viewport(player, map, view_pos) < 0)
		return(-ERROR_MALLOC);
	display = false;
	return (NO_ERROR);
}
