/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: von <von@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 19:30:26 by tseche            #+#    #+#             */
/*   Updated: 2026/05/19 21:37:47 by von              ###   ########.fr       */
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
	int		len;// 12
	int		iter;
	int		ori_x;
	int		ori_y;
	float	door;
}				t_map_simu;


typedef enum	s_error_map_gen{
	MAP_EMPTY_GEN,
	ERROR_MAX_BNS
}				t_error_map_map;

void    free_str(char **chose);
void    	free_t_map_simu(t_map_simu **map);
void		throw_error_bonus(int err);
bool    	map_empty(t_map_simu *map);
bool		between(int a, int b, int c);
bool		had_space_neighbour(t_map_simu *map, int x, size_t y);
void		place_door(t_map_simu *map);
void		get_range(int *range, int *seed);
long int			gen_seed();
t_map_simu	*seed_to_mapsimu(long int seed);
void		simulate(t_map_simu *map);
int			*spawn(t_map_simu *map);
char	**get_map_from_simu(t_map_simu *map);
void 	debug_seed(t_map_simu *map, long int seed);
void	apply_wall(t_map_simu *map);
#endif