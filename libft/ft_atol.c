/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 17:54:00 by tseche            #+#    #+#             */
/*   Updated: 2026/01/08 18:04:16 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

long	ft_atol(const char *str)
{
	int		i;
	int		sign;
	long	res;

	res = 0;
	i = 0;
	sign = 1;
	i += skip_spaces((char *)str);
	if (str[i] && (str[i] == '+' || str[i] == '-'))
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	i += skip_spaces((char *)str);
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
		res = (res * 10) + (str[i++] - '0');
	return (res * sign);
}
