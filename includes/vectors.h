/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcaplat <pcaplat@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 18:51:18 by pcaplat           #+#    #+#             */
/*   Updated: 2026/05/10 01:23:07 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

typedef struct s_vect
{
	float	x;
	float	y;
}			t_vect;

typedef struct	s_vect3
{
	float	x;
	float	y;
	float	z;
}			t_vect3;

void	set_vect(t_vect *vect, float x, float y);
t_vect	vect_multiply(const t_vect v, float factor);
t_vect	vect_sum(const t_vect v1, const t_vect v2);

#endif
