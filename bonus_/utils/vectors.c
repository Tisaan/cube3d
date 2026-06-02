/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: von <von@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 00:26:14 by pcaplat           #+#    #+#             */
/*   Updated: 2026/06/01 16:34:14 by von              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_vect(t_vect *vect, float x, float y)
{
	vect->x = x;
	vect->y = y;
}

t_vect	vect_sum(const t_vect v1, const t_vect v2)
{
	t_vect	new_v;

	new_v.x = v1.x + v2.x;
	new_v.y = v1.y + v2.y;
	return (new_v);
}

t_vect	vect_multiply(const t_vect v, float factor)
{
	t_vect	new_v;

	new_v.x = v.x * factor;
	new_v.y = v.y * factor;
	return (new_v);
}

void	rotate_vect(t_vect *vect, float angle)
{
	float	cos_a;
	float	sin_a;
	float	old_x;

	cos_a = cosf(angle);
	sin_a = sinf(angle);
	old_x = vect->x;
	vect->x = vect->x * cos_a - vect->y * sin_a;
	vect->y = old_x * sin_a + vect->y * cos_a;
}

void	normalize(t_vect *vect, float speed)
{
	float	lenght;

	lenght = sqrtf(vect->x * vect->x + vect->y * vect->y);
	if (lenght > speed)
	{
		vect->x = vect->x / lenght * speed;
		vect->y = vect->y / lenght * speed;
	}
}
