/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 00:26:14 by pcaplat           #+#    #+#             */
/*   Updated: 2026/05/10 09:45:30 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
