/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 11:25:47 by pcaplat           #+#    #+#             */
/*   Updated: 2026/05/12 21:16:01 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
#include <sys/time.h>

typedef struct s_data	t_data;

typedef struct	s_timer
{
	struct timeval	current_time;
	struct timeval	start_time;
	float			fps;
}					t_timer;

void	free_all(t_data *data, int fd);
void	clean_exit(t_data *data);
float	ft_abs(float nb);

//timer
void	time_update(void *param);
void	start_timer(t_timer *timer);

#endif
