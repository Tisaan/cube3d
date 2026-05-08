/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 11:23:24 by tseche            #+#    #+#             */
/*   Updated: 2026/05/07 18:34:08 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus.h"
#include "../../includes/vectors.h"


int	spawn_safe(int **map, int *pos)
{
	if (!map[pos[0]][pos[1]])
		return (-1);
	return (map[pos[0]][pos[1]] == 1);
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
		npos = (int *)(int [3]){pos[0] + 2, pos[1] + num, sum};
	}
	else if (i % 4 == 1)
	{
		sum = pos[0] - 2 + pos[1] + num;
		npos = (int *)(int [3]){pos[0] - 2, pos[1] + num, sum};
	}
	else if (i % 4 == 2)
	{
		sum = pos[0] + num + pos[1] + 2;
		npos = (int *)(int [3]){pos[0] + num, pos[1] + 2, sum};
	}
	else
	{
		sum = pos[0] + num + pos[1] - 2;
		npos = (int *)(int [3]){pos[0] + num, pos[1] - 2, sum};
	}
	return (npos);
}

int	*spawn(t_map_simu *map){
	int	*c_pos;
	int     i;
	bool	check;
	int		err;

	c_pos = (int [3]){map->height / 2, map->width / 2, 0};
	i = 0;
	check = true;
	while (check){
		c_pos = l_shape(c_pos, i);
		err = spawn_safe(map->map, c_pos);
		if (err == -1)
			c_pos = (int [3]){map->height / 2, map->width / 2, 0};
		else if (err)
			check = false;
		i++;
	}
	return (c_pos);
}
