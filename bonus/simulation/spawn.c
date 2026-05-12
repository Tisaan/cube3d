/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 11:23:24 by tseche            #+#    #+#             */
/*   Updated: 2026/05/09 18:14:57 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus.h"
#include "../../includes/vectors.h"
#include <stdio.h>
#include <stdlib.h>


int	spawn_safe(t_map_simu *map, int *pos)
{

	if (!(pos[0] <= map->height && pos[1] <= map->width))
		return (-2);
	if (map->map[pos[0]][pos[1]] && map->map[pos[0]][pos[1]] == '0')
		return (-1);
	return (map->map[pos[0]][pos[1]] == 1);
}

int	*l_shape(int *pos, int i){
	int			*npos;
	const int 	table[3] = {-1, 0, 1};
	int			num;
	int			sum;

	num = table[i % 3];
	if (i % 4 == 0)
	{
		sum = pos[0] + 2 + pos[1] + num;
		npos[0] = pos[0] + 2;
		npos[1] = pos[1] + num;
		npos[2] = sum;
	}
	else if (i % 4 == 1)
	{
		sum = pos[0] - 2 + pos[1] + num;
		npos[0] = pos[0] - 2;
		npos[1] = pos[1] + num;
		npos[2] = sum;
	}
	else if (i % 4 == 2)
	{
		sum = pos[0] + num + pos[1] + 2;
		
		npos[0] = pos[0] + num;
		npos[1] = pos[1] + 2;
		npos[2] = sum;
	}
	else
	{
		sum = pos[0] + num + pos[1] - 2;
		npos[0] = pos[0] + num;
		npos[1] = pos[1] - 2;
		npos[2] = sum;
	}
	return (npos);
}

int	*spawn(t_map_simu *map){
	int	*c_pos;
	int     i;
	bool	check;
	int		err;

	c_pos = malloc(sizeof(int) * 3);
	c_pos[0] = map->height / 2;
	c_pos[1] = map->width / 2;
	c_pos[2] = 0;
	check = true;
	while (check && i < 50){
		c_pos = l_shape(c_pos, i);
		err = spawn_safe(map, c_pos);
		if (err == -1)
		{
			c_pos[0] = map->height / 2;
			c_pos[1] = map->width / 2;
			c_pos[2] = 0;
		}
		else if (err)
			check = false;
		i++;
	}
	if (i == 50)
	{
		c_pos[0] = -1;
		c_pos[1] = 0;
		c_pos[2] = 0;
	}
	return (c_pos);
}
