/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: von <von@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 15:15:18 by tseche            #+#    #+#             */
/*   Updated: 2026/05/18 15:54:03 by von              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus.h"

bool	had_space_neighbour(t_map_simu *map, int x, size_t y)
{
	int i;
	int	j;

	i = -1;
	while (i <= 1)
	{
		j = -1;
		while (j <= 1)
		{
			if (map->map[(map->height + i + x) % map->height][(map->width + j + y) % map->width] == ' ')
				return (true);
		}
		
	}
	return (false);
}


