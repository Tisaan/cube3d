/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 19:30:26 by tseche            #+#    #+#             */
/*   Updated: 2026/06/03 13:06:16 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_H
# define BONUS_H

#include "cub3d.h"
#include <pthread.h>

#define dir_x {1, -1, 1, 0, 0, -1, 1, -1}
#define dir_y {-1, 1, -1, 0, 0, 1, -1, 1}

//----------[tweak de la gen]------
#define big
#if defined(big)
# define variant_gen_y (i + map->ori_y)
# define variant_gen_x (i + map->ori_x)
#elif defined(mini)
# define variant_gen_x (i)
# define variant_gen_y (i)
#else
# define variant_gen_x (i + map->ori_y + map->ori_x)
# define variant_gen_y (i + map->ori_y + map->ori_x)
#endif

typedef struct s_int3
{
	int	zero;
	int	one;
	int	two;
}				t_int3;

typedef struct s_int2
{
	int	zero;
	int	one;
}				t_int2;

typedef struct s_point
{
	int x;
	int y;
}				t_point;

typedef struct	s_pointlist
{
	t_point	*point;
	int		curr;
	int		len;
	int		size_max;
}				t_pointlist;

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
	int		count;
}				t_map_simu;

typedef enum	s_error_map_gen
{
	ERR_ARGS,
	SEED_INVALID,
	MAP_EMPTY_GEN,
	MAP_NO_SPAWN,
	ERR_MALLOC_BNS,
	ERROR_MAX_BNS
}				t_error_map_map;


//-----------[pointlist/method.c]-----
t_pointlist	*initpoints(int size);
int	addpoint(t_pointlist *l, t_point p);
void	resetpointlist(t_pointlist *l);
void	free_pointlist(t_pointlist *l);

//----------[utils.c]-----------
int			add_digit_number(long int nb);
void		throw_error_bonus(int err);
bool    	map_empty(t_map_simu *map);
bool		had_space_neighbour(t_map_simu *map, int x, size_t y);
void		int_to_bin_str(unsigned long num, char *dest);
int			nb_zero_neighbour(t_map_simu *map, int x, size_t y);

//----------[free.c]-----------
void		free_t_map_simu(t_map_simu *map);

//----------[door.c]-----------
void		place_door(t_map_simu *map);
void		apply_wall(t_map_simu *map);

//----------[gen_seed.c]-----------
long int	gen_seed();
t_map_simu	*seed_to_mapsimu(long int seed);
bool		check_seed(long seed);
void 		debug_seed(t_map_simu *map, long int seed, bool print);

//----------[spawn.c]-----------
int			place_spawn(t_map_simu *map);
t_map		*convert_map_simu_to_map(t_map_simu *map);

//----------[main_proc.c]-------
t_data	*main_proc(long int seed);

#endif