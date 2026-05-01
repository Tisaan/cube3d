/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 11:23:04 by tseche            #+#    #+#             */
/*   Updated: 2026/05/01 14:05:40 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	throw_error(int err)
{
	err = abs(err);
	if (err <= ERROR_MAX)
	{
		ft_putstr_fd((char *)g_errors[err], 2);
	}
	else
	{
		ft_putstr_fd("Unknown error code", 2);
	}
}
