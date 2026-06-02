/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 14:19:36 by von               #+#    #+#             */
/*   Updated: 2026/06/02 16:39:49 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bonus.h"
#include "../includes/debug.h"

void	set_default(t_data *data)
{
	data->plans_color[0] = (t_prgb){.type = CEILING, .rgb[0] = 200, .rgb[1] = 180, .rgb[2]= 160};
	data->plans_color[1] = (t_prgb){.type = FLOOR, .rgb[0] = 255, .rgb[1] = 255, .rgb[2]= 255};
	data->texture[0] = (t_texture_path){.path = "assets/bluestone.png", .dir = NO};
	data->texture[1] = (t_texture_path){.path = "assets/bluestone.png", .dir = SO};
	data->texture[2] = (t_texture_path){.path = "assets/greystone.png", .dir = WE};
	data->texture[3] = (t_texture_path){.path = "assets/greystone.png", .dir = EA};
	
}