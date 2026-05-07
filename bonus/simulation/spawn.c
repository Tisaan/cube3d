/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 11:23:24 by tseche            #+#    #+#             */
/*   Updated: 2026/05/07 11:24:22 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus.h"
#include "../../includes/vector.h"

t_vect3		find_center(t_map *map)
{
	return ((t_vect3){.x = map.height / 2; .y = map.width / 2; .z = 0})
}

int	spawn_safe(t_map *map, t_vect pos)
{
	if (!map->grid[pos.x][pox.y])
		return (-1);
	return (map->grid[pos.x][pox.y] == '0');
}

t_vect3	l_shape(t_map *map, t_vect3 pos, int i){
	t_vect3		npos;
	const int 	table[3] = {-1, 0, 1};
	int			num;
	int			sum;

	num = table[i % 3];
	switch (i % 4){
		case (0):{
			sum = pos.x + 2 + pos.y + num;
			npos = (t_vect){.x = pos.x + 2; .y = pos.y + num, .z = sum};
		}
		case (1):{
			sum = pos.x - 2 + pos.y + num;
			npos = (t_vect){.x = pos.x - 2; .y = pos.y + num, .z = sum};
		}
		case (2):{
			sum = pos.x + num + pos.y + 2;
			npos = (t_vect){.x = pos.x + num; .y = pos.y + 2, .z = sum};
		}
		case (3):{
			sum = pos.x + num + pos.y - 2;
			npos = (t_vect){.x = pos.x + num; .y = pos.y - 2, .z = sum};
		}
	}
	return (npos);
}

t_vect3	spawn(t_map *map){
	t_vect3	c_pos;
	int     i;
	bool	check;

	c_pos = find_center(map);
	i = 0;
	check = true;
	while (check){
		c_pos = l_shape(c_pos, i);
		err = spawn_safe(map, c_pos)
		if (err == -1)
			c_pos = find_center(map);
		else if (err)
			check = false;
		i++;
	}
	return (c_pos);
}
