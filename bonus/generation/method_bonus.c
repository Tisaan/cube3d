/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   method_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 17:56:26 by von               #+#    #+#             */
/*   Updated: 2026/06/03 17:09:05 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bonus.h"

t_pointlist	*initpoints(int size)
{
	t_pointlist	*list;

	list = ft_calloc(sizeof(t_pointlist), 1);
	if (!list)
		return (NULL);
	list->point = ft_calloc(sizeof(t_point), size);
	if (!list->point)
	{
		free(list);
		return (NULL);
	}
	list->curr = 0;
	list->len = 0;
	list->size_max = size;
	return (list);
}

int	addpoint(t_pointlist *l, t_point p)
{
	if (l->len == l->size_max)
		return (-1);
	l->point[l->curr++] = p;
	l->len++;
	return (1);
}

void	resetpointlist(t_pointlist *l)
{
	l->len = 0;
	l->curr = 0;
}

void	free_pointlist(t_pointlist *l)
{
	free(l->point);
	free(l);
}
