/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 17:54:23 by tseche            #+#    #+#             */
/*   Updated: 2026/01/10 18:30:22 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
The  memcpy()  function  copies  n bytes from memory area src to memory area
dest in ascending order.  The memory areas must not overlap.
Use memmove(3) if the memory  areas do overlap.
*/
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*ret;

	ret = dest;
	while (n--)
		*(unsigned char *)dest++ = *(unsigned char *)src++;
	return (ret);
}
