/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 10:26:08 by pcaplat           #+#    #+#             */
/*   Updated: 2026/06/15 17:57:37 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"
#include "../includes/mini_map_bonus.h"

static char	*dup_viewport_line(t_player *p, t_map *map, int map_x, int map_y)
{
	char	*line;
	int		i;

	line = malloc(sizeof(char) * (11 + 1));
	i = 0;
	while (line && map_x < 0 && i < 11)
	{
		line[i++] = ' ';
		map_x++;
	}
	while (line && map->grid[map_y][map_x] && i < 11)
	{
		if (map_y == p->pos.y / WALL_SIZE && map_x == p->pos.x / WALL_SIZE)
			line[i++] = 'P';
		else if (ft_isoneof(map->doors[map_y][map_x], "10"))
			line[i++] = 'D';
		else
			line[i++] = map->grid[map_y][map_x];
		map_x++;
	}
	while (line && i < 11)
		line[i++] = ' ';
	if (line)
		line[i] = '\0';
	return (line);
}

void	free_viewport(t_data *data)
{
	int	i;

	if (!data->map->viewport)
		return ;
	i = 0;
	while (data->map->viewport[i])
		free(data->map->viewport[i++]);
	free(data->map->viewport);
}

void	clear_viewport(t_map *map, int i)
{
	while (i >= 0)
		free(map->viewport[--i]);
	free(map->viewport);
}

int	fill_viewport(t_player *player, t_map *map, t_point view)
{
	int	map_y;
	int	i;

	map_y = view.y;
	i = 0;
	if (fill_start_with_space(map, &i, &map_y) != 0)
		return (-ERROR_MALLOC);
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
	if (fill_end_with_space(map, &i) != 0)
		return (-ERROR_MALLOC);
	map->viewport[i] = NULL;
	return (NO_ERROR);
}
