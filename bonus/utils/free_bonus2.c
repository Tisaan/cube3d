/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 15:24:27 by tseche            #+#    #+#             */
/*   Updated: 2026/06/15 15:30:02 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	free_doors_map(t_data *d)
{
	int	i;

	i = 0;
	while (d->map->doors[i])
		free(d->map->doors[i++]);
	free(d->map->doors);
}
