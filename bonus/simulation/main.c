/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 17:42:13 by tseche            #+#    #+#             */
/*   Updated: 2026/05/07 17:56:53 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus.h"

int main()
{
	const int	*range = get_range(1, NULL);
	int			seed = gen_seed(range[0], range[1]);
	t_map_simu	*map = seed_to_mapsimu(seed);
	char		**map = simulate(map);
	int			*spawn_point = spawn(map);
}