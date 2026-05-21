/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 19:30:26 by tseche            #+#    #+#             */
/*   Updated: 2026/05/21 18:17:13 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_H
# define BONUS_H

#include "cub3d.h"

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
}				t_map_simu;

typedef struct s_coord	
{
	int row;
	int col;
}				t_coord;
typedef struct s_group
{
	t_coord *coords;
	int count;
}				t_group_gen;

typedef struct s_two_group
{
	t_group_gen first;
	t_group_gen second;
} 				t_two_group;

typedef enum	s_error_map_gen{
	MAP_EMPTY_GEN,
	ERROR_MAX_BNS
}				t_error_map_map;


//----------[group.c]-----------
t_two_group find_biggest_groups(t_map_simu *map, int num_rows);
void free_group(t_group_gen *g);

//----------[utils.c]-----------
int		add_digit_number(long int nb);
void		throw_error_bonus(int err);
bool    	map_empty(t_map_simu *map);
bool		had_space_neighbour(t_map_simu *map, int x, size_t y);

//----------[free.c]-----------
void	free_t_map_simu(t_map_simu *map);

//----------[door.c]-----------
void		place_door(t_map_simu *map);
void		apply_wall(t_map_simu *map);

//----------[gen_seed.c]-----------
long int		gen_seed();
t_map_simu		*seed_to_mapsimu(long int seed);
void 			debug_seed(t_map_simu *map, long int seed, bool print);

#endif