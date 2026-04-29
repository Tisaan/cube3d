/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strendwith.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 18:11:30 by tseche            #+#    #+#             */
/*   Updated: 2026/04/29 16:33:45 by pcaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

bool	ft_strendwith(char *s, char *pattern)
{
	s += ft_strlen(s) - ft_strlen(pattern);
	while (*s && *s == *pattern && s++ && pattern ++)
		;
	if (!*s)
		return (true);
	return (false);
}
