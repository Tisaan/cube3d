/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:43:17 by tseche            #+#    #+#             */
/*   Updated: 2026/04/28 19:24:52 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

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


#endif