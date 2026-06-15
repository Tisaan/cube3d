/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strendwith.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 18:11:30 by tseche            #+#    #+#             */
/*   Updated: 2026/06/15 16:03:51 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

bool	ft_strendwith(char *s, char *pattern)
{
	int	len_s;
	int	len_p;

	len_s = ft_strlen(s);
	len_p = ft_strlen(pattern);
	if (len_s < len_p)
		return (false);
	s += len_s - len_p;
	while (*s && *s == *pattern && s++ && pattern ++)
		;
	if (!*s)
		return (true);
	return (false);
}
