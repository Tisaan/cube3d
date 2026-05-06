/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 19:30:26 by tseche            #+#    #+#             */
/*   Updated: 2026/05/06 20:10:40 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_H
# define BONUS_H

#include "cub3d.h"

typedef	struct s_map_seed
{
	struct s_map map; 
	int		seed;
}				t_map_seed;

#endif