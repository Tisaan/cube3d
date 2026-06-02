/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: von <von@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 11:04:11 by pcaplat           #+#    #+#             */
/*   Updated: 2026/06/02 14:56:40 by von              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/player.h"



void	display_player_data(t_player *player)
{
	printf("=== PLAYER DATA ===\n");
	printf("player start: (%f, %f)\n", player->pos.x, player->pos.y);
	printf("size: %d\n", player->size);
}

void	display_map_data(t_data data)
{
	printf("%d: <%s>\n", data.texture[0].dir, data.texture[0].path);
	printf("%d: <%s>\n", data.texture[1].dir, data.texture[1].path);
	printf("%d: <%s>\n", data.texture[2].dir, data.texture[2].path);
	printf("%d: <%s>\n", data.texture[3].dir, data.texture[3].path);
	printf("Ceiling color: (%d, %d, %d)\tFloor color: (%d, %d, %d)\n", data.plans_color[CEILING - 5].rgb[0],data.plans_color[CEILING - 5].rgb[1],data.plans_color[CEILING - 5].rgb[2],
		data.plans_color[FLOOR - 5].rgb[0],data.plans_color[FLOOR - 5].rgb[1],data.plans_color[FLOOR - 5].rgb[2]);
	printf("Map:\n");
	for (int i = 0; i < data.map->height; i++)
		printf("%s", data.map->grid[i]);
	printf("start:\n x:%d\ny:%d\ndir:%d\n", data.map->start[0], data.map->start[1], data.map->start[2]);
}

void	ft_print_error(const char *msg)
{
	write(2, msg, ft_strlen(msg));
}

void	init_pip_boy(t_img *img, t_data *data)
{
	img->asset = mlx_new_image_from_file(data->mlx, "assets/pip_boy.png", &img->width, &img->height);
}
