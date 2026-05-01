/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:22:03 by tseche            #+#    #+#             */
/*   Updated: 2026/05/01 12:18:29 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	get_rel_path(char *line)
{
	int	len;
	int	dot;
	int	slash;

	len = 0;
	dot = 0;
	slash = 0;
	while (!ft_isalpha(*line))
	{
		if (*line == '/' && slash == 0)
			dot = 0;
		else if (*line == '.' && dot <= 2)
			dot++;
		else if (*line == '/' || *line == '.')
			return (-ERROR_INV_PATH_TEXTURE);
		else if (*line == '"' || *line == '\'')
			return (-ERROR_INV_PATH_TEXTURE);
		line++;
		len++;
	}
	return (len);
}

int	len_path(char *line, int quote[2])
{
	char	*cpy;

	cpy = line;
	while (*line && *line != '\n')
	{
		if ((*line == '(' || *line == ')') && quote[1])
			break ;
		else if (*line == '(' || *line == ')')
			return (-ERROR_INV_PATH_TEXTURE);
		else if (*line == '\'' && (quote[1] == 0 || quote[0] == '\''))
			return (-ERROR_INV_PATH_TEXTURE);
		else if (*line == '"' && (quote[1] == 0 || quote[0] == '"'))
			return (-ERROR_INV_PATH_TEXTURE);
		line++;
	}
	return (line - cpy);
}

char *get_path(char *line)
{
	int		quote[2];
	char	*str;
	int		pre;
	char	*cpy;
	int		len;

	cpy = line;
	line += skip_spaces(line);
	if (*line == '\'' || *line == '"'){
		quote[1] = 1;
		quote[0] = *line++;
 	}
	pre = get_rel_path(line);
	if (pre == -ERROR_INV_PATH_TEXTURE)
		return (NULL);
	len = len_path(line, quote);
	if (len == -ERROR_INV_PATH_TEXTURE)
		return (NULL);
	str = ft_substr(cpy, 0, pre + line - cpy + len);
	if (!str)
		return (NULL);
	return (str);
}
