/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:43:17 by tseche            #+#    #+#             */
/*   Updated: 2026/05/01 15:56:57 by tseche           ###   ########.fr       */
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
	INV_MAP,
	INV_CUT_MAP, 
	INV_WALL_MAP,
	NOT_ENO_STRT,
	TOO_MUCH_STRT,
	MISS_TEXTURE,
	MISS_COLOR,
	ERROR_INV_PATH_TEXTURE,
	ERROR_OPEN,
	ERROR_OPEN_TEXTURE,
	ERROR_PATH_TEXTURE,
	ERROR_INV_COLOR,
	ERROR_MALLOC,
	ERROR_MAX,
}		t_error_map;

static const char	*g_errors[ERROR_MAX] = {
("WTF an error has been "
		"thrown, but no error was detected\n"),
"the map provided is not a .cub file\n",
"An unrecognize character has been found\n",
"the map is empty\n",
"the map is cut in multiple part\n",
"the map is not properly walled\n",
"The Map contains no starting point\n",
"The map cointains too much starting point\n",
"A texture path is missing\n",
"A color is missing in the map\n",
"Invalid texture path provided\n",
"A file couldn't be opened\n",
"A texture file couldn't be opened\n",
"The path of one of the texture is invalid\n",
"Invalid color format, < 0 or > 255\n",
"Erreur malloc\n",
};

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

typedef struct s_vect
{
	float	x;
	float	y;
	float	z;
}				t_vect;

typedef struct s_map
{
	char	**grid;
	t_vect	*player_pos;
	int		width;
	int		height;
	int		*start;// [0] = x, [1] = y, [2] = direction
}				t_map;

t_data	parse(char *map_path);
int		get_map(int fd, t_map *data, int size, int skip);
int		walled(t_map *map);
int		get_start(t_map *map);
int		check_map(t_map *map);


// --- PATH ---
char	*get_path(char *line);
int		map_size(char *name);

// --- ERROR --- 
void	throw_error(int err);

// --- UTILS ---
int		get_identifier(char *line);
int		rgb_str_to_int(char	*str, t_prgb *color);
void	free_all(t_data *data);

#endif
