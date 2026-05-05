/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 11:23:04 by tseche            #+#    #+#             */
/*   Updated: 2026/05/05 12:00:04 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

const char	**get_tab_error(void)
{
	static const char	*error[ERROR_MAX] = {
		("WTF an error has been "
			"thrown, but no error was detected\n"),
		"the map provided is not a .cub file\n",
		"An unrecognize character has been found\n",
		"the map is empty\n",
		"Invalid map\n",
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
		("Invalid color format, make sure to use only"
			" 3 unsigned short numbers !\n"),
		"Erreur malloc\n",
	};

	return ((const char **)error);
}

void	throw_error(int err)
{
	const char	**error = get_tab_error();

	err = abs(err);
	if (err <= ERROR_MAX)
	{
		ft_putstr_fd((char *)error[err], 2);
	}
	else
	{
		ft_putstr_fd("Unknown error code", 2);
	}
}
