/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 11:23:04 by tseche            #+#    #+#             */
/*   Updated: 2026/06/15 18:03:00 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	add_error(char **error)
{
	error[ERROR_MALLOC] = "Malloc Error\n";
	error[ERROR_ARGS] = "Invalid number of arguments.\n";
}

static inline char	**get_tab_error(void)
{
	static char	*error[ERROR_MAX] = {
		"WTF an error has been thrown\n",
		"the map provided is not a .cub file\n",
		"An unrecognize character has been found\n",
		"the map is empty\n",
		"Invalid map\n",
		"the map is cut in multiple part\n",
		"the map is not properly walled\n",
		"The Map contains no starting point\n",
		"The map contains too much starting point\n",
		"A texture path is missing\n",
		"A color is missing in the map\n",
		"Failed to load wall asset\n",
		"Invalid image size\n",
		"Invalid texture path provided\n",
		"A texture path is defined multiple times\n",
		"A file couldn't be opened\n",
		"A texture file couldn't be opened\n",
		"The path of one of the texture is invalid\n",
		("Invalid color format, make sure to use only"
			" 3 unsigned short numbers !\n"),
	};

	add_error(error);
	return ((char **)error);
}

void	throw_error(int err)
{
	char	**error;

	error = get_tab_error();
	err = abs(err);
	ft_putstr_fd("Error\n", 2);
	if (err <= ERROR_MAX)
	{
		ft_putstr_fd((char *)error[err], 2);
	}
	else
	{
		ft_putstr_fd("Unknown error code", 2);
	}
}
