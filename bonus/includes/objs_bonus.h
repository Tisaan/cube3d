/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objs_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 12:14:07 by pcaplat           #+#    #+#             */
/*   Updated: 2026/06/15 14:45:10 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJS_BONUS_H
# define OBJS_BONUS_H

# include "raycast_bonus.h"
# include "cub3d_bonus.h"

typedef struct s_obj
{
	int		start;
	int		end;
	int		height;
	int		cliping;
}		t_obj;

t_obj	get_obj(t_win_infos *win, float wall_dist);

#endif
