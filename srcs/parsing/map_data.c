/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 11:07:21 by pcaplat           #+#    #+#             */
/*   Updated: 2026/05/01 16:00:55 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	init_map_data(t_data *data)
{
	data->texture[0].path = NULL;
	data->texture[1].path = NULL;
	data->texture[2].path = NULL;
	data->texture[3].path = NULL;
	data->plans_color[0].type = EMPT;
	data->plans_color[1].type = EMPT;
}

int	parse_map_data(int fd, t_data *data, int *count)
{
	char	*line;
	int		id;
	int		i;
	bool	match;

	line = get_next_line(fd);
	*count += 1;
	init_map_data(data);
	while (line)
	{
		i = 0;
		while(line && ft_isempty(line))
		{
			free(line);
			line = get_next_line(fd);
			*count += 1;
		}
		if (line && line[i])
			i += skip_spaces(&line[i]);
		if (line && (line[i] == '0' || line[i] == '1'))
			break ;
		id = get_identifier(&line[i]);
		if (line && line[i] && (id == FLOOR || id == CEILING))
		{
			match = line[i] == 'F';
			i++;
			if (rgb_str_to_int(&line[i], &data->plans_color[match]) == -ERROR_INV_COLOR)
			{
				free(line);
				return (-ERROR_INV_COLOR);
			}
			data->plans_color[match].type = match;
		}
		else if (line && line[i] && id != INV)
		{
			i += 2;
			i += skip_pattern(&line[i], "\t \r");
			if (!line || !line[i] || line[i] == '\n')
			{
				free(line);
				return (-ERROR_INV_PATH_TEXTURE);
			}
			data->texture[id].dir = id;
			if (line[i])
				data->texture[id].path = get_path(&line[i]);
			if (data->texture[id].path == NULL)
			{
				free(line);
				free_all(data);
				return (-ERROR_MALLOC);
			}
		}
		else
		{
			free(line);
			return (-ERROR_INV_PATH_TEXTURE);
		}
		free(line);
		line = get_next_line(fd);
		*count  += 1;
	}
	return (NO_ERROR);
}
