/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: von <von@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 19:43:53 by von               #+#    #+#             */
/*   Updated: 2026/05/19 21:38:37 by von              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus.h"

void    free_t_map_simu(t_map_simu **map)
{
    int i;

    i = 0;
    while (i <= (*map)->height)
    {
        free((* map)->map[i]);
        i++;
    }
    free((* map)->map);
    free(*map);
}

void    free_str(char **chose)
{
    free(*chose);
}