/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 11:11:39 by pcaplat           #+#    #+#             */
/*   Updated: 2026/05/12 14:52:54 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include <sys/time.h>

float	ft_abs(float nb)
{
	if (nb < 0) 
		return (nb * -1);
	return (nb);
}

void	start_timer(t_timer *timer)
{
	gettimeofday(&timer->start_time, NULL);
	timer->current_time = (struct timeval){0};
	timer->fps = 0.0;
}

void	time_update(t_timer *timer, float *delta)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	*delta = (time.tv_sec - timer->current_time.tv_sec) + (time.tv_usec - timer->current_time.tv_usec) / 1000000.0;
	timer->current_time = time;
	if (*delta > 0)
		timer->fps = 1.0 / *delta;
	else
		timer->fps = 0.0;
}
