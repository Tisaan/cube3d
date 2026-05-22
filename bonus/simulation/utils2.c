/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 16:05:33 by tseche            #+#    #+#             */
/*   Updated: 2026/05/22 16:14:18 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	int_to_bin_str(unsigned long num, char *dest)
{
	unsigned long	mask;
	int				index;

	if (num == 0)
	{
		ft_strcpy(dest, "0", 1);
		return ;
	}
	mask = 1UL << (sizeof(unsigned long) * 8 - 1);
	index = 0;
	while ((num & mask) == 0)
		mask >>= 1;
	while (mask != 0)
	{
		if (num & mask)
			dest[index++] = '1';
		else
			dest[index++] = '0';
		mask >>= 1;
	}
	dest[index] = '\0';
}
