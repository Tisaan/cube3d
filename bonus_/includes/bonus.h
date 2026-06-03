/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 19:30:26 by tseche            #+#    #+#             */
/*   Updated: 2026/06/03 19:05:58 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_H
# define BONUS_H

# include "cub3d.h"
# include <pthread.h>

# define DIR_X {1, -1, 1, 0, 0, -1, 1, -1}
# define DIR_Y {-1, 1, -1, 0, 0, 1, -1, 1}

//----------[tweak de la gen]------
# define BIG
# if defined(BIG)
#  define VARIANT_GEN_Y (i + map->ori_y)
#  define VARIANT_GEN_X (i + map->ori_x)
# elif defined(MINI)
#  define VARIANT_GEN_X (i)
#  define VARIANT_GEN_Y (i)
# else
#  define VARIANT_GEN_X (i + map->ori_y + map->ori_x)
#  define VARIANT_GEN_Y (i + map->ori_y + map->ori_x)
# endif

typedef struct s_int3
{
	int	zero;
	int	one;
	int	two;
}				t_int3;

typedef struct s_point
{
	int	x;
	int	y;
}				t_point;

typedef struct s_pointlist
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
	char	*seed;
}				t_map_simu;

typedef enum s_error_map_gen
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
int			addpoint(t_pointlist *l, t_point p);
void		resetpointlist(t_pointlist *l);
void		free_pointlist(t_pointlist *l);

//----------[utils.c]-----------
int			add_digit_number(long int nb);
void		throw_error_bonus(int err);
bool		map_empty(t_map_simu *map);
bool		had_space_neighbour(t_map_simu *map, int x, size_t y);
void		int_to_bin_str(unsigned long num, char *dest);
int			nb_zero_neighbour(t_map_simu *map, int x, size_t y);
void		place_zero(t_map_simu *map, int i, int j);
void		place_point(t_map_simu *map, t_point prev, t_point pos);
bool		addpointfree(t_pointlist *list, t_point pos, t_map_simu *map);
bool		place_gen_algo(t_point *pos, t_map_simu *map,
				t_pointlist *list, int i);
void		l_shape(t_point *pos, int i, t_map_simu *map);
void		place_point_loop(t_map_simu *map, t_pointlist *p);
t_map_simu	*init_map(t_data *data, long int seed);
bool		place_bound(t_map_simu *map, t_point *pos, int *index,
				t_pointlist *list);
bool		generate_map(t_map_simu *map, long int seed);

//----------[free.c]-----------
void		free_t_map_simu(t_map_simu *map);

//----------[door.c]-----------
void		place_door(t_map_simu *map);
void		apply_wall(t_map_simu *map);

//----------[gen_seed.c]-----------
long int	gen_seed(void);
t_map_simu	*seed_to_mapsimu(long int seed);
bool		check_seed(long seed);
void		debug_seed(t_map_simu *map, long int seed, bool print);

//----------[spawn.c]-----------
int			place_spawn(t_map_simu *map);
t_map		*convert_map_simu_to_map(t_map_simu *map);

//----------[main_proc.c]-------
t_data		*main_proc(long int seed);

#endif