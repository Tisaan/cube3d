/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: von <von@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 17:42:13 by tseche            #+#    #+#             */
/*   Updated: 2026/05/13 21:19:39 by von              ###   ########.fr       */
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
	flag = true;
	for (int i = 0; i <= map->height; i++)
	{
		num = 0;
		while (num < map->width)
		{
			if (flag)
			{
				if (num % 2)
					num += ft_strlcat(&map->map[i][num], bfloor, 33);
				else 
					num += ft_strlcat(&map->map[i][num], bspace, 33);
			}
			else
			{
				if (num % 2)
					num += ft_strlcatrev(&map->map[i][num], bspace, 33);
				else 
					num += ft_strlcatrev(&map->map[i][num], bfloor, 33);
			}
		}
		map->map[i][map->width] = 0;
		flag = !flag;
	}
}

int main()
{
	int	range[2];
	get_range(range, NULL);
	int			seed = gen_seed(range[0], range[1]);
	t_map_simu	*map = seed_to_mapsimu(seed);

	debug_seed(map, seed);
	map->map = ft_calloc(map->height + 1, sizeof(int *));
	for (int i = 0; i <= map->height; i++)
		map->map[i] = ft_calloc(sizeof(int), map->width + 1);
	
	make_grid(map);
	printf("map:\n");
	for (int i = 0; i <= map->height; i++)
		printf("%s\n", map->map[i]);
	printf("end\n");
	simulate(map);
	printf("map:\n");
	for (int i = 0; i <= map->height; i++)
		printf("%s\n", map->map[i]);
	printf("end\n");
	int			*spoint = spawn(map);
	printf("spawn[%d]\n", spoint[0]);
	if (spoint[0] == -1)
		printf("no spawn found\n");
	else
		map->map[spoint[0]][spoint[1]] = "NSEW"[spoint[2]];
	
	for (int i = 0; i <= map->height; i++)
		free(map->map[i]);
	free(spoint);
	free(map->map);
	free(map);
}