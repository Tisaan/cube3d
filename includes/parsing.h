/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:43:17 by tseche            #+#    #+#             */
/*   Updated: 2026/05/01 11:09:59 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

// --- ERROR ---

typedef enum e_error_map
{
	NO_ERROR,
	INC_EXT,
	INC_WALL,
	INC_CHAR,
	INV_MAP,
	INV_CUT_MAP,
	INV_WALL_MAP,
	NOT_ENO_STRT,
	TOO_MUCH_STRT,
	ERROR_INV_PATH_TEXTURE,
	ERROR_OPEN,
	ERROR_OPEN_TEXTURE,
	ERROR_PATH_TEXTURE,
	ERROR_MALLOC,
	ERROR_MAX,
}		t_error_map;

static const char	*g_errors[ERROR_MAX] = {
("WTF an error has been"
		"thrown, but no error was detected\n"),
"the map provided is not a .cub file\n",
"The map hasn't been properly walled\n",
"An unrecognize character has been found\n",
"the map is empty\n",
"the map is cut in multiple part",
"the is not properly walled",
"The Map contains no starting point\n",
"The map cointains too much starting point\n",
"Invalid texture path provided",
"A file couldn't be opened\n",
"A texture file couldn't be opened\n",
"The path of one the texture is invalid",
"Erreur malloc\n",
};
// --- STRUCT ---

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
	CEILING,
	FLOOR
}			t_pceilfloor;

typedef struct s_prgb{
	int rgb[3];
	t_pceilfloor type;
}				t_prgb;

typedef struct s_data	t_data;

t_data	parse(char *map_path);
char	*get_path(char *line);


// --- PATH ---
char	*get_path(char *line);
int		map_size(char *name);

#endif
