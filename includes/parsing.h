/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:43:17 by tseche            #+#    #+#             */
/*   Updated: 2026/05/09 22:11:07 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

// --- ERROR ---

typedef enum e_error_map
{
	NO_ERROR,
	INC_EXT,
	INC_CHAR,
	EMPT_MAP,
	INV_MAP,
	INV_CUT_MAP, 
	INV_WALL_MAP,
	NOT_ENO_STRT,
	TOO_MUCH_STRT,
	MISS_TEXTURE,
	MISS_COLOR,
	ERROR_LOAD_ASSET,
	ERROR_INV_PATH_TEXTURE,
	ERROR_OPEN,
	ERROR_OPEN_TEXTURE,
	ERROR_PATH_TEXTURE,
	ERROR_INV_COLOR,
	ERROR_MALLOC,
	ERROR_MAX,
}		t_error_map;

// --- STRUCT ---

typedef struct s_data	t_data;

// ---- TEXTURE ----

typedef enum e_direction_id{
	NO,
	SO,
	WE,
	EA,
	INV
}				t_direction_id;

typedef struct s_texture_path
{
	char			*path;
	t_direction_id	dir;
}				t_texture_path;

typedef enum e_pceilfloor{
	CEILING = 5,
	FLOOR = 6,
	EMPT
}			t_pceilfloor;

typedef struct s_prgb{
	int rgb[3];
	t_pceilfloor type;
}				t_prgb;

// ---- MAP ----

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		*start;// [0] = x, [1] = y, [2] = direction
}				t_map;

t_data	parse(char *map_path);
int		get_map(int fd, t_map *data);
int		walled(t_map *map);
int		get_start(t_map *map);
int		check_map(t_map *map);
int		parse_map_data(int fd, t_data *data, int *count);

// --- INIT ---

void	init_map_data(t_data *data);
int		init_game(t_data *data);

// --- PATH ---
char	*get_path(char *line);
int		map_size(char *name);

// --- ERROR --- 
void	throw_error(int err);

// --- UTILS ---
int		get_identifier(char *line);
int		rgb_str_to_int(char	*str, t_prgb *color);
int		check_map_data(t_data data, char *line);
char	*repline(char *line, int fd, int *rep, int count);
bool	is_pattern_char_present(char *line, char *pat);
int		check_char_present_map(char *line, int *find_end, int len);
int		line_wall(t_map *map, int *ij, int *first, int *find);
bool	around(t_map *map, int x, size_t y);
int		get_dir(int c);
#endif
