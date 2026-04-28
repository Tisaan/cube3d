/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 16:21:47 by marvin            #+#    #+#             */
/*   Updated: 2026/01/16 16:12:28 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_ft_strlen(char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
		i++;
	return (i);
}

char	*gnl_ft_strdup(char *src)
{
	size_t	len;
	char	*ret;
	size_t	i;

	len = gnl_ft_strlen(src);
	i = 0;
	ret = malloc((len + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	while (src[i])
	{
		ret[i] = src[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char	*gnl_ft_strchr(char *src, char lf)
{
	size_t	i;
	size_t	len;

	len = gnl_ft_strlen(src);
	i = 0;
	while (i <= len)
	{
		if (src[i] == lf)
			return (src + i);
		i++;
	}
	return (NULL);
}

char	*gnl_ft_strjoin(char *po, char *pt)
{
	size_t	len_po;
	size_t	len_pt;
	size_t	i;
	char	*ret;

	len_po = gnl_ft_strlen(po);
	len_pt = gnl_ft_strlen(pt);
	i = 0;
	ret = malloc((len_po + len_pt + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	while (po[i])
	{
		ret[i] = po[i];
		i++;
	}
	i = 0;
	while (pt[i])
	{
		ret[len_po + i] = pt[i];
		i++;
	}
	ret[len_po + i] = '\0';
	return (ret);
}

char	*gnl_ft_substr(char *src, unsigned int start, size_t len)
{
	char	*ret;
	size_t	i;

	ret = malloc((len + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ret[i] = src[start + i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
