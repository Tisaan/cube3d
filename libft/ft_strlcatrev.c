/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcatrev.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 20:24:13 by von               #+#    #+#             */
/*   Updated: 2026/06/15 18:04:23 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcatrev(char *dest, const char *src, size_t size)
{
	size_t	l;

	l = ft_strnlen(dest, size);
	if (l == size)
	{
		l += ft_strlen(src);
		return (l);
	}
	l += ft_strlcpy(dest + l, src, size - l);
	return (l);
}
