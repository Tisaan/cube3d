/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 14:19:36 by von               #+#    #+#             */
/*   Updated: 2026/06/12 18:27:21 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bonus.h"
#include "../includes/debug.h"

static int	set_default_texture(t_data *data)
{
	int			i;
	int			ret;
	int			j;
	const char	*table[] = {"assets/bluestone.png", "assets/greystone.png"};

	i = 0;
	ret = 0;
	while (i < 4 && ret == 0)
	{
		data->texture[i] = (t_texture_path){.path = ft_substr(table[i > 1], 0,
				21), .dir = i};
		if (!data->texture[i].path)
		{
			ret = ERROR_MALLOC;
			break ;
		}
		i++;
	}
	if (ret == 0)
		return (NO_ERROR);
	j = 0;
	while (j <= i)
		free(data->texture[j++].path);
	return (ret);
}

int	set_default(t_data *data)
{
	data->plans_color[0] = (t_prgb){.type = CEILING, .rgb[0] = 200,
		.rgb[1] = 180, .rgb[2] = 160};
	data->plans_color[1] = (t_prgb){.type = FLOOR, .rgb[0] = 255, .rgb[1] = 255,
		.rgb[2] = 255};
	if (set_default_texture(data) < 0)
		return (-ERROR_MALLOC);
	return (NO_ERROR);
}

char	*str_seed(long int n)
{
	char	*s;
	int		i;

	s = ft_calloc(sizeof(char), 13);
	if (!s)
		return (s);
	s[12] = '\0';
	i = 12;
	while (i--)
	{
		s[i] = (n % 10) + '0';
		n /= 10;
	}
	return (s);
}
