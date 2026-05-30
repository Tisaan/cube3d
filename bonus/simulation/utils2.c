/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: von <von@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 16:05:33 by tseche            #+#    #+#             */
/*   Updated: 2026/05/30 12:25:58 by von              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus.h"

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
		nx = x + ((int [8])dir_x)[i];
		ny = y + ((int [8])dir_y)[i];
		if (nx >= 0 && nx < map->height && ny >= 0 && ny < map->width)
		{
			if (map->map[nx][ny] == '0')
				count++;
		}
		i++;
	}
	return (count);
}
