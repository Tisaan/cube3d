/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpyrev.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: von <von@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 20:25:02 by von               #+#    #+#             */
/*   Updated: 2026/05/13 20:26:52 by von              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpyrev(char *dst, const char *src, size_t size)
{
	char	*tmp;
    int     i;

	tmp = dst;
    i = ft_strlen(src);
	if (!size--)
		return (ft_strlen(src));
	while (*src && size && size--)
		*dst++ = src[i--];
	*dst = '\0';
	return (dst - tmp + ft_strlen(src));
}