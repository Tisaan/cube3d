/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 17:42:13 by tseche            #+#    #+#             */
/*   Updated: 2026/05/12 14:45:37 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus.h"

void	int_to_bin_str(unsigned int num, char *s)
{
	unsigned int	mask;
	int				index;

	if (num == 0)
	{
		ft_strcpy(s, "0", 1);
		return ;
	}
	mask = 1 << (sizeof(unsigned int) * 8 - 1);
	index = 0;
	while ((num & mask) == 0)
		mask >>= 1;
	while (mask != 0){
		if (num & mask)
			s[index++] = '1';
		else
			s[index++] = '0';
		mask >>= 1;
	}
	s[index] = 0;
}

void	make_grid(t_map_simu *map)
{
	char bfloor[33];
	char bspace[33];
	bool	flag;
	int		num;

	int_to_bin_str(map->floor, bfloor);
	int_to_bin_str(map->space, bspace);
	write(1, "f:", 2);
	write(1, bfloor, ft_strlen(bfloor));
	write(1, "\n", 1);
	write(1, "s:", 1);
	write(1, bspace, ft_strlen(bspace));
	write(1, "\n", 1);
	flag = true;
	for (int i = 0; map->map[i]; i++)
	{
		num = 0;
		while ((map->width - num) > 0)
		{
			if (flag)
			{
				if (num % 2)
					num += ft_strlcat(map->map[i], bfloor, 33);
				else 
					num += ft_strlcat(map->map[i], bspace, 33);
			}
			else
			{
				if (num % 2)
					num += ft_strlcat(map->map[i], bspace, 33);
				else 
					num += ft_strlcat(map->map[i], bfloor, 33);
			}
		}
		flag = !flag;
	}
}

int main()
{
	int	range[2];
	get_range(range, NULL);
	int			seed = gen_seed(range[0], range[1]);
	t_map_simu	*map = seed_to_mapsimu(seed);
	map->map = ft_calloc(map->height + 1, sizeof(int *));
	debug_seed(map);

	for (int i = 0; i < map->height; i++)
	{
		map->map[i] = ft_calloc(sizeof(int), map->width + 1);
		map->map[map->width] = 0;
	}
	make_grid(map);
	write(1, "out", 3);
	printf("map:\n");
	for (int i = 0; map->map[i]; i++)
		printf("%s\n", map->map[i]);
	printf("end\n");
	simulate(map);
	printf("map:\n");
	for (int i = 0; map->map[i]; i++)
		printf("%s\n", map->map[i]);
	printf("end\n");
	//int			*spoint = spawn(map);
	//printf("spawn[%d]\n", spoint[0]);
	// if (spoint[0] == -1)
	// 	printf("no spawn found\n");
	// else
	// 	map->map[spoint[0]][spoint[1]] = "NSEW"[spoint[2]];
	
	for (int i = 0; i < map->height; i++)
		free(map->map[i]);
	free(map->map);
	free(map);
}