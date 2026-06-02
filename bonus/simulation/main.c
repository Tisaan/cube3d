/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: von <von@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 17:42:13 by tseche            #+#    #+#             */
/*   Updated: 2026/05/31 18:10:52 by von              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus.h"



int	main(int ac, char **av)
{
	t_map_simu	*map;
	long int	seed;
	
	int				i;

	
	debug_seed(map, seed, 1);
	debug_seed(map, seed, 0);
	free_t_map_simu(map);
}
