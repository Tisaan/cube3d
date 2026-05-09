/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 19:30:26 by tseche            #+#    #+#             */
/*   Updated: 2026/05/09 17:09:16 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_H
# define BONUS_H

#include "cub3d.h"

typedef	struct s_map_seed
{
	struct s_map map; 
	int		seed;
}				t_map_seed;

// ' ' => 0 stay, 4 to '0' 
// 0 => 1 stay, 5 to 1
// 1 => 2 stay, 6 to ' '
typedef struct s_map_simu
{
	char	**map;
	int		height;
	int		width;
	int		len;// 7 / 8
	int		stof;// space to floor, ' ' => '0'
	int		ftof;// stay floor
	int		ftow;// floor to wall, '0' => '1'
	int		wtos;// wall to space, '1' => ' '
	int		iter;
	float	door;// e.g: 0.7 = 70%
	bool	wall;// 0 => 0 to 1, 1 => ' ' => 1
	int		min;
	int		max;
}				t_map_simu;


bool		between(int a, int b, int c);
bool		had_space_neighbour(t_map_simu *map, int x, size_t y);
void		place_door(t_map_simu *map);
void		get_range(int *range, int cycle, int *seed);
int			gen_seed(int min, int max);
t_map_simu	*seed_to_mapsimu(int seed);
void		simulate(t_map_simu *map);
int			*spawn(t_map_simu *map);
char	**get_map_from_simu(t_map_simu *map);
void 	debug_seed(t_map_simu *map);
#endif