/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:50:52 by marvin            #+#    #+#             */
/*   Updated: 2026/01/16 16:11:14 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

char	*get_next_line(int fd);

size_t	gnl_ft_strlen(char *src);

char	*gnl_ft_strdup(char *src);

char	*gnl_ft_strchr(char *src, char lf);

char	*gnl_ft_strjoin(char *po, char *pt);

char	*gnl_ft_substr(char *src, unsigned int start, size_t len);
#endif