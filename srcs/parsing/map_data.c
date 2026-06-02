/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 11:07:21 by pcaplat           #+#    #+#             */
/*   Updated: 2026/06/01 07:27:07 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/utils.h"
#include "../../includes/debug.h"

static int	parse_colors(t_data *data, char *line, int *i, int id)
{
	bool	match;

	if (line && line[*i] && (id == FLOOR || id == CEILING))
	{
		match = line[*i] == 'F';
		*i += 1;
		if (rgb_str_to_int(&line[*i], &data->plans_color[match]) < 0)
		{
			free(line);
			return (-ERROR_INV_COLOR);
		}
		data->plans_color[match].type = match;
	}
	return (NO_ERROR);
}

static int	parse_texture(t_data *data, char *line, int *i, int id)
{
	int	ret;

	if (line && line[*i] && id != INV && id != CEILING && id != FLOOR)
	{
		*i += 2;
		*i += skip_pattern(&line[*i], "\t \r");
		if (!line || !line[*i] || ft_isempty(&line[*i]))
		{
			free(line);
			return (-ERROR_INV_PATH_TEXTURE);
		}
		ret = set_texture_path(data->texture, line, id, i);
		if (ret < 0)
		{
			free(line);
			return (ret);
		}
	}
	if (id == INV)
	{
		free(line);
		return (-ERROR_INV_PATH_TEXTURE);
	}
	return (NO_ERROR);
}

static int	skip_until_id(char **line, int fd)
{
	int	i;

	i = 0;
	while (*line && ft_isempty(*line))
	{
		free(*line);
		*line = get_next_line(fd);
	}
	if (*line && (*line)[i])
		i += skip_spaces(&((*line)[i]));
	return (i);
}

static int	parse_map_loop(t_data *data, char *line, int *i)
{
	int	id;
	int	ret;

	id = get_identifier(&line[*i]);
	if (parse_colors(data, line, i, id) < 0)
		return (-ERROR_INV_COLOR);
	ret = parse_texture(data, line, i, id);
	if (ret < 0)
		return (ret);
	else if (ret != 0)
	{
		free(line);
		return (-ERROR_INV_PATH_TEXTURE);
	}
	return (NO_ERROR);
}

int	parse_map_data(int fd, t_data *data, int *count)
{
	char	*line;
	int		i;
	int		ret;

	init_map_data(data);
	ret = INV_MAP;
	line = get_next_line(fd);
	*count += 1;
	while (line)
	{
		i = skip_until_id(&line, fd);
		if (line && (line[i] == '0' || line[i] == '1'))
			break ;
		ret = parse_map_loop(data, line, &i);
		if (ret < 0)
			return (ret);
		ret = check_map_data(*data, line);
		if (ret == NO_ERROR)
			return (ret);
		line = get_next_line(fd);
		*count += 1;
	}
	ret *= (ret > 0) * -1 + (ret <= 0) * 1;
	free(line);
	return (ret);
}
