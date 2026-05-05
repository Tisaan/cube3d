/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 11:56:21 by pcaplat           #+#    #+#             */
/*   Updated: 2026/05/05 12:21:15 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_map_data(t_data *data)
{
	data->texture[0].path = NULL;
	data->texture[1].path = NULL;
	data->texture[2].path = NULL;
	data->texture[3].path = NULL;
	data->plans_color[0].type = EMPT;
	data->plans_color[1].type = EMPT;
}
