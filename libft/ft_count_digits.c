/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_digits.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 03:44:32 by tseche            #+#    #+#             */
/*   Updated: 2026/05/15 14:43:53 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_digits(long int n)
{
	int	count;

	if (!n)
		return (1);
	count = 0;
	if (n < 0)
	{
		++count;
		n *= -1;
	}
	while (n > 9)
	{
		n /= 10;
		++count;
	}
	++count;
	return (count);
}
