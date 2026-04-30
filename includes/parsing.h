/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:43:17 by tseche            #+#    #+#             */
/*   Updated: 2026/04/30 15:03:46 by tseche           ###   ########.fr       */
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
	INC_SHAPE,
	INV_MAP,
	NOT_ENO_STRT,
	TOO_MUCH_STRT,
	NOT_ENO_COLL,
	NOT_ENO_FINISH,
	TOO_MUCH_FINISH,
	NOT_REACH_COLL,
	NOT_REACH_FINISH,
	ERROR_SIZE,
	ERROR_WIN,
	ERROR_OPEN,
	ERROR_OPEN_XPM,
	ERROR_MALLOC,
	ERROR_PATH_TEXT,
	ERROR_MAX,
}		t_error_map;

static const char	*g_errors[ERROR_MAX] = {
("WTF an error has been"
		"thrown, but no error was detected\n"),
"the map provided is not a .ber file\n",
"The map hasn't been properly walled\n",
"An unrecognize character has been found\n",
"The Map is not a rectangle\n",
"the map is empty\n",
"The Map contains no starting point\n",
"The map cointains too much starting point\n",
"The Map contains no collectible\n",
"The Map contains no exit\n",
"The map contain too much finish\n",
"The Map contains a not reachable collectible\n",
"The Map contains a not reachable exit\n",
"The map is limited to 100 * 100 duw to stack limitation\n",
"The map is limited due to screen size limitation\n",
"A file couldn't be opened\n",
"A XPM file couldn't be opened\n",
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

#endif
