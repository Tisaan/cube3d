/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: von <von@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 12:11:53 by pcaplat           #+#    #+#             */
/*   Updated: 2026/06/01 16:33:42 by von              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast.h"
#include "../includes/objs.h"

t_obj	get_obj(t_win_infos *win, float wall_dist)
{
	t_obj	obj;

	obj.height = (int)(win->height / wall_dist);
	obj.start = -obj.height / 2 + win->height / 2;
	obj.end = obj.height / 2 + win->height / 2;
	obj.cliping = 0;
	if (obj.start < 0)
	{
		obj.cliping = -obj.start;
		obj.start = 0;
	}
	if (obj.end > win->height)
		obj.end = win->height;
	return (obj);
}
