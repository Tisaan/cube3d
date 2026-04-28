/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 20:10:58 by tseche            #+#    #+#             */
/*   Updated: 2026/01/26 16:50:46 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	*ft_realloc(void *p, size_t n)
{
	void	*ptr;

	ptr = malloc(n);
	if (!ptr)
		return (NULL);
	if (p)
		ft_memcpy(ptr, p, n - 1);
	((unsigned char *)ptr)[n - 1] = 0;
	free(p);
	return (ptr);
}
