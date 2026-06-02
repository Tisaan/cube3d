/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: von <von@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 11:09:16 by pcaplat           #+#    #+#             */
/*   Updated: 2026/06/01 16:32:31 by von              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	get_identifier(char *line)
{
	if (ft_strncmp(line, "NO", 2) == 0 && line[2] && ft_isspace(line[2]))
		return (NO);
	if (ft_strncmp(line, "SO", 2) == 0 && line[2] && ft_isspace(line[2]))
		return (SO);
	if (ft_strncmp(line, "WE", 2) == 0 && line[2] && ft_isspace(line[2]))
		return (WE);
	if (ft_strncmp(line, "EA", 2) == 0 && line[2] && ft_isspace(line[2]))
		return (EA);
	if (ft_strncmp(line, "F", 1) == 0 && line[1] && ft_isspace(line[1]))
		return (FLOOR);
	if (ft_strncmp(line, "C", 1) == 0 && line[1] && ft_isspace(line[1]))
		return (CEILING);
	return (INV);
}

static int	skip_non_digit(char *str, int *i)
{
	while (str && str[*i] && !ft_isdigit(str[*i]))
	{
		if (ft_isalpha(str[*i]) || str[*i] == '-')
			return (-ERROR_INV_COLOR);
		*i += 1;
	}
	return (NO_ERROR);
}

int	rgb_str_to_int(char	*str, t_prgb *color)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	color->rgb[0] = -1;
	color->rgb[1] = -1;
	color->rgb[2] = -1;
	while (str && str[i] && j < 3)
	{
		if (skip_non_digit(str, &i) < 0)
			return (-ERROR_INV_COLOR);
		if (!str[i])
			break ;
		color->rgb[j] = ft_atoi(&str[i]);
		if (color->rgb[j] < 0 || color->rgb[j] > 255)
			return (-ERROR_INV_COLOR);
		i += skip_digits(&str[i]);
		j++;
	}
	if (ft_isempty(&str[i]) && j == 3)
		return (NO_ERROR);
	return (-ERROR_INV_COLOR);
}

int	check_map_data(t_data data, char *line)
{
	t_texture_path	*texture;
	t_prgb			*colors;

	free(line);
	texture = data.texture;
	colors = data.plans_color;
	if (texture[0].path == NULL || texture[1].path == NULL
		|| texture[2].path == NULL || texture[3].path == NULL)
		return (-MISS_TEXTURE);
	if (colors[0].type == EMPT || colors[1].type == EMPT)
		return (-MISS_COLOR);
	return (NO_ERROR);
}
