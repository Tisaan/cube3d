/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 16:52:40 by tseche            #+#    #+#             */
/*   Updated: 2026/06/06 14:41:37 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	init_map_door(t_data *data)
{
	int	i;
	int	j;

	data->map_door = ft_calloc(data->map->height + 1, sizeof(t_state_obj *));
	if (!data->map_door)
		return (-ERROR_MALLOC);
	i = 0;
	while (i < data->map->height)
	{
		data->map_door[i] = ft_calloc(data->map->width + 1, sizeof(t_state_obj));
		if (!data->map_door[i])
		{
			ft_freeptr((void **)data->map_door);
			return (-ERROR_MALLOC);
		}
		i++;
	}
	i = 0;
	while (i < data->map->height)
	{
		j = 0;
		while (j < data->map->width)
		{
			if (data->map->grid[i][j] == 'D')
				data->map_door[i][j] = close_state;
			else
				data->map_door[i][j] = not_door_state;
			j++;
		}
		i++;
	}
	return (0);
}
