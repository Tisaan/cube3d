/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpyrev.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 20:25:02 by von               #+#    #+#             */
/*   Updated: 2026/06/15 18:05:22 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpyrev(char *dst, const char *src, size_t size)
{
	char	*tmp;
	int		i;

	tmp = dst;
	i = ft_strlen(src);
	if (!size--)
		return (ft_strlen(src));
	while (*src && size && size--)
		*dst++ = src[i--];
	*dst = '\0';
	return (dst - tmp + ft_strlen(src));
}
