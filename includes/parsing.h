/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:43:17 by tseche            #+#    #+#             */
/*   Updated: 2026/04/29 15:40:45 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "cub3d.h"

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
	ERROR_MAX,
}		t_error_map;

static const char	*g_errors[ERROR_MAX] = {
[NO_ERROR] = ("WTF an error has been"
		"thrown, but no error was detected\n"),
[INC_EXT] = "the map provided is not a .ber file\n",
[INC_WALL] = "The map hasn't been properly walled\n",
[INC_CHAR] = "An unrecognize character has been found\n",
[INC_SHAPE] = "The Map is not a rectangle\n",
[INV_MAP] = "the map is empty\n",
[NOT_ENO_STRT] = "The Map contains no starting point\n",
[TOO_MUCH_STRT] = "The map cointains too much starting point\n",
[NOT_ENO_COLL] = "The Map contains no collectible\n",
[NOT_ENO_FINISH] = "The Map contains no exit\n",
[TOO_MUCH_FINISH] = "The map contain too much finish\n",
[NOT_REACH_COLL] = "The Map contains a not reachable collectible\n",
[NOT_REACH_FINISH] = "The Map contains a not reachable exit\n",
[ERROR_SIZE] = "The map is limited to 100 * 100 duw to stack limitation\n",
[ERROR_WIN] = "The map is limited due to screen size limitation\n",
[ERROR_OPEN] = "A file couldn't be opened\n",
[ERROR_OPEN_XPM] = "A XPM file couldn't be opened\n",
[ERROR_MALLOC] = "Erreur malloc\n",
};
// --- STRUCT ---

typedef enum e_eptexture{
	NO,
	SO,
	WE,
	EA,
}				t_eptexture;

typedef struct s_texture_path
{
	char *path;
	t_eptexture dir;
}				t_texture_path;

typedef enum e_pceilfloor{
	CEILING,
	FLOOR
}			t_pceilfloor;

typedef struct s_prgb{
	int rgb[3];
	t_pceilfloor type;
}				t_prgb;

t_data	parse(char *map_path);

#endif
