/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: von <von@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 11:11:39 by pcaplat           #+#    #+#             */
/*   Updated: 2026/06/15 14:06:47 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"
#include <sys/time.h>

inline float	ft_abs(float nb)
{
	if (nb < 0)
		return (nb * -1);
	return (nb);
}

mlx_color	rgb_to_color(t_prgb rgb, int alpha)
{
	mlx_color	color;

	if (alpha < 0)
		alpha = 0;
	color.r = rgb.rgb[0];
	color.g = rgb.rgb[1];
	color.b = rgb.rgb[2];
	color.a = alpha;
	return (color);
}

void	start_timer(t_timer *timer)
{
	gettimeofday(&timer->start_time, NULL);
	timer->current_time = timer->start_time;
	timer->fps = 0.0;
}

void	time_update(void *param)
{
	struct timeval	time;
	t_data			*data;

	data = (t_data *)param;
	gettimeofday(&time, NULL);
	data->delta = (time.tv_sec - data->timer.current_time.tv_sec)
		+ (time.tv_usec - data->timer.current_time.tv_usec) / 1000000.0;
	data->timer.current_time = time;
	if (data->delta > 0)
		data->timer.fps = 1.0 / data->delta;
	else
		data->timer.fps = 0.0;
}

int	clamp_pos(int p, int min, int max)
{
	if (p < min)
		return (min);
	if (p > max)
		return (max);
	return (p);
}
