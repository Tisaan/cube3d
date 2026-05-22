/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 19:30:26 by tseche            #+#    #+#             */
/*   Updated: 2026/05/22 15:25:31 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_H
# define BONUS_H

#include "cub3d.h"

typedef struct s_int3
{
	int	zero;
	int	one;
	int	two;
}				t_int3;

typedef struct s_map_simu
{
	char	**map;
	int		height;
	int		width;
	int		len;// 12
	int		iter;
	int		ori_x;
	int		ori_y;
	float	door;
	t_int3	spawn;
}				t_map_simu;

typedef enum	s_error_map_gen{
	MAP_EMPTY_GEN,
	MAP_NO_SPAWN,
	ERROR_MAX_BNS
}				t_error_map_map;




//----------[utils.c]-----------
int			add_digit_number(long int nb);
void		throw_error_bonus(int err);
bool    	map_empty(t_map_simu *map);
bool		had_space_neighbour(t_map_simu *map, int x, size_t y);

//----------[free.c]-----------
void		free_t_map_simu(t_map_simu *map);

//----------[door.c]-----------
void		place_door(t_map_simu *map);
void		apply_wall(t_map_simu *map);

//----------[gen_seed.c]-----------
long int	gen_seed();
t_map_simu	*seed_to_mapsimu(long int seed);
void 		debug_seed(t_map_simu *map, long int seed, bool print);

//----------[spawn.c]-----------
int			place_spawn(t_map_simu *map);
t_map		*convert_map_simu_to_map(t_map_simu *map);

#endif