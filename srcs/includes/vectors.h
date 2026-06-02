/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: von <von@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 18:51:18 by pcaplat           #+#    #+#             */
/*   Updated: 2026/05/30 15:07:19 by von              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

 typedef struct s_vect
{
	float	x;
	float	y;
}			t_vect;

void	set_vect(t_vect *vect, float x, float y);
void	rotate_vect(t_vect *vect, float angle);
t_vect	vect_multiply(const t_vect v, float factor);
t_vect	vect_sum(const t_vect v1, const t_vect v2);
void	normalize(t_vect *vect, float speed);

#endif
