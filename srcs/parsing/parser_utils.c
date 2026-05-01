/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 11:09:16 by pcaplat           #+#    #+#             */
/*   Updated: 2026/05/01 13:36:19 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	get_identifier(char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (NO);
	if (ft_strncmp(line, "SO ", 3) == 0)
		return (SO);
	if (ft_strncmp(line, "WE ", 3) == 0)
		return (WE);
	if (ft_strncmp(line, "EA ", 3) == 0)
		return (EA);
	if (ft_strncmp(line, "F ", 2) == 0)
		return (FLOOR);
	if (ft_strncmp(line, "C ", 2) == 0)
		return (CEILING);
	return (INV);
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
		while(str && str[i] && !ft_isdigit(str[i]))
		{
			if (ft_isalpha(str[i]) || str[i] == '-')
				return (-ERROR_INV_COLOR);
			i++;
		}
		if (!str[i])
			break ;
		color->rgb[j] = ft_atoi(&str[i]);
		if (color->rgb[j] < 0 || color->rgb[j] > 255)
			return (-ERROR_INV_COLOR);
		i += skip_digits(&str[i]);
		j++;
	}
	return (1);
}
