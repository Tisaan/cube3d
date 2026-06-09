/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 12:14:07 by pcaplat           #+#    #+#             */
/*   Updated: 2026/06/09 15:10:10 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJS_H
# define OBJS_H

# include "raycast.h"
# include "cub3d.h"

typedef struct s_obj
{
	int		start;
	int		end;
	int		height;
	int		cliping;
	union
	{
		t_state_obj	state;
	};
}		t_obj;

t_obj	get_obj(t_win_infos *win, float wall_dist);

#endif
