/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat </var/spool/mail/pcaplat>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 12:14:07 by pcaplat           #+#    #+#             */
/*   Updated: 2026/05/28 13:22:59 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJS_H
# define OBJS_H

# include "raycast.h"

typedef struct s_obj
{
	int	start;
	int	end;
	int	height;
	int	cliping;
}		t_obj;

t_obj	get_obj(t_win_infos *win, float wall_dist);

#endif
