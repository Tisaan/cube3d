/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_gen_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 16:05:33 by tseche            #+#    #+#             */
/*   Updated: 2026/06/15 14:15:17 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bonus.h"

void	int_to_bin_str(unsigned long num, char *dest)
{
	unsigned long	mask;
	int				index;

	if (num == 0)
	{
		ft_strcpy(dest, "0", 1);
		return ;
	}
	mask = 1UL << (sizeof(unsigned long) * 8 - 1);
	index = 0;
	while ((num & mask) == 0)
		mask >>= 1;
	while (mask != 0)
	{
		if (num & mask)
			dest[index++] = '1';
		else
			dest[index++] = '0';
		mask >>= 1;
	}
	dest[index] = '\0';
}

int	nb_zero_neighbour(t_map_simu *map, int x, size_t y)
{
	int			i;
	int			nx;
	int			ny;
	int			count;

	i = 0;
	count = 0;
	while (i < 8)
	{
		nx = x + map->dir_x[i];
		ny = y + map->dir_y[i];
		if (nx >= 0 && nx < map->height && ny >= 0 && ny < map->width)
		{
			if (map->map[nx][ny] == '0')
				count++;
		}
		i++;
	}
	return (count);
}

void	place_zero(t_map_simu *map, int i, int j)
{
	if (map->map[i - 2][j] == '0')
		map->map[i - 1][j] = '0';
	if (map->map[i + 2][j] == '0')
		map->map[i + 1][j] = '0';
	if (map->map[i][j - 2] == '0')
		map->map[i][j - 1] = '0';
	if (map->map[i][j + 2] == '0')
		map->map[i][j + 1] = '0';
	if (map->map[i - 2][j - 2] == '0')
		map->map[i - 1][j - 2] = '0';
	if (map->map[i + 2][j + 2] == '0')
		map->map[i + 1][j + 2] = '0';
	if (map->map[i - 2][j + 2] == '0')
		map->map[i - 1][j + 2] = '0';
	if (map->map[i + 2][j - 2] == '0')
		map->map[i + 1][j - 2] = '0';
}

void	place_point(t_map_simu *map, t_point prev, t_point pos)
{
	while (prev.x < pos.x || prev.y < pos.y)
	{
		if (prev.y < pos.y)
			map->map[prev.x][++prev.y] = '0';
		if (prev.x < pos.x)
			map->map[++prev.x][prev.y] = '0';
	}
	while (prev.x > pos.x || prev.y > pos.y)
	{
		if (prev.y > pos.y)
			map->map[prev.x][--prev.y] = '0';
		if (prev.x > pos.x)
			map->map[--prev.x][prev.y] = '0';
	}
}

bool	addpointfree(t_pointlist *list, t_point pos, t_map_simu *map)
{
	if ((pos.x < map->height && pos.x >= 0)
		&& (pos.y < map->width && pos.y >= 0))
	{
		if (addpoint(list, pos) < 0)
		{
			place_point_loop(map, list);
			free_pointlist(list);
			return (false);
		}
	}
	return (true);
}
