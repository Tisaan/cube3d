/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skip_pattern.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 17:32:57 by tseche            #+#    #+#             */
/*   Updated: 2026/01/11 20:50:06 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

int	skip_digits(char *s)
{
	char	*src;

	src = s;
	if (!s || !*s)
		return (0);
	if (*s == '+' || *s == '-')
		s++;
	while (*s >= '0' && *s <= '9')
		s++;
	return (s - src);
}

int	skip_spaces(char *s)
{
	char	*src;

	src = s;
	if (!s || !*s)
		return (0);
	while (((*s >= 0 && *s <= 13) || *s == ' ') && s++)
		;
	return (s - src);
}

int	skip_pattern(char *s, char *pattern)
{
	char	*src;

	src = s;
	while (*s && ft_isoneof(*s, pattern) && s++)
		;
	return (s - src);
}
