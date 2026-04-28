/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:22:03 by tseche            #+#    #+#             */
/*   Updated: 2026/04/28 19:25:19 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_texture_path *get_texture_path(char **content){
	int				pos;
	t_texture_path	text[4];
	int				exist[4];
	char			*tmp;

	pos = 0;
	while (content[pos])
	{
		exist[NO] += ft_strncmp(content[pos], "NO", 2) == 0;
		
		if (exist[NO])
		{
			content[pos] += 2;
			text[NO].dir = NO;
			tmp = ft_substr(content[pos], skip_spaces(content[pos]),
					ft_strlen(content[pos]) - skip_spaces(content[pos]));
			if (!tmp)
				return (NULL);
			text[NO].path = tmp;
			exist[NO] = 1;
		}
		else if (ft_strncmp(content[pos], "SO", 2) == 0 && exist[SO] == 0)
		{
			content[pos] += 2;
			text[SO].dir = SO;
			tmp = ft_substr(content[pos], skip_spaces(content[pos]),
					ft_strlen(content[pos]) - skip_spaces(content[pos]));
			if (!tmp)
				return (NULL);
			text[SO].path = tmp;
			exist[SO] = 1;
		}
		else if (ft_strncmp(content[pos], "WE", 2) == 0 && exist[WE] == 0)
		{
			content[pos] += 2;
			text[WE].dir = WE;
			tmp = ft_substr(content[pos], skip_spaces(content[pos]),
					ft_strlen(content[pos]) - skip_spaces(content[pos]));
			if (!tmp)
				return (NULL);
			text[WE].path = tmp;
			exist[WE] = 1;
		}
		else if (ft_strncmp(content[pos], "NO", 2) == 0 && exist[EA] == 0)
		{
			content[pos] += 2;
			text[EA].dir = EA;
			tmp = ft_substr(content[pos], skip_spaces(content[pos]),
					ft_strlen(content[pos]) - skip_spaces(content[pos]));
			if (!tmp)
				return (NULL);
			text[EA].path = tmp;
			exist[EA] = 1;
		}
		else if ()
		if (exist[NO] && exist[SO] && exist[WE] && exist[EA]){
			return (text);
		}
		
	}
	return (text);
}


bool check_map(char *name){
	if (!ft_strendwith(name, ".cub"))
		return (false);
	return (true);
}
