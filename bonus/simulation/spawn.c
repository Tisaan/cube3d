/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 11:23:24 by tseche            #+#    #+#             */
/*   Updated: 2026/05/07 11:42:59 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus.h"
#include "../../includes/vectors.h"

int	*find_center(t_map *map)
{
	return ((int *)(int [3]){map->height / 2, map->width / 2, 0});
}

int	spawn_safe(t_map *map, int *pos)
{
	if (!map->grid[pos[0]][pos[1]])
		return (-1);
	return (map->grid[pos[0]][pos[1]] == '0');
}

int	*l_shape(t_map *map, int *pos, int i){
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
	else if (i % 4 == 3)
	{
		sum = pos[0] + num + pos[1] - 2;
		npos = (int *)(int [3]){pos[0] + num, pos[1] - 2, sum};
	}
	return (npos);
}

int	*spawn(t_map *map){
	int	*c_pos;
	int     i;
	bool	check;
	int		err;

	c_pos = find_center(map);
	i = 0;
	check = true;
	while (check){
		c_pos = l_shape(map, c_pos, i);
		err = spawn_safe(map, c_pos);
		if (err == -1)
			c_pos = find_center(map);
		else if (err)
			check = false;
		i++;
	}
	return (c_pos);
}
