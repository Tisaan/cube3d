/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: von <von@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 19:30:26 by tseche            #+#    #+#             */
/*   Updated: 2026/05/27 16:20:39 by von              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_H
# define BONUS_H

#include "cub3d.h"
#include <pthread.h>

typedef struct s_int3
{
	int	zero;
	int	one;
	int	two;
}				t_int3;

typedef struct s_point
{
	int row;
	int col;
}				t_point;

//-------------[BFS]-------------

//-------------[QUEUE]-----------
typedef struct 	s_queue{
    t_point 		*data;
    int				front;
	int				rear;
	int				capacity;
	pthread_mutex_t	mutex;
}				t_queue;

//-------------[PATH]-----------
typedef struct s_path{
    t_point *points;
    int count;
    int capacity;
} 				t_path;

//------------[DATA]------------
typedef struct {
    t_queue *forward_queue;
	t_queue	*backward_queue;
    bool 	**forward_visited;
	bool	**backward_visited;
    t_point **forward_parent;
	t_point	**backward_parent;
    char 	**grid;
    int		rows;
	int		cols;
    t_point start;
	t_point end;
	t_point	meeting_point;
    bool found;
    pthread_mutex_t found_mutex;
    pthread_cond_t found_cond;
} BFSData;

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

//----------[Queue/method.c]-------
t_queue* create_queue(int capacity);
void enqueue(t_queue *q, t_point p);
t_point dequeue(t_queue *q);
bool is_empty(t_queue *q);
void free_queue(t_queue *q);

//----------[Path/method.c]-------
t_path* create_path(int capacity);
void add_to_path(t_path *p, t_point t_point);
void reverse_path(t_path *p);
t_path* find_shortest_path(char **grid, int rows, int cols, t_point start, t_point end);

#endif