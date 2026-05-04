/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 11:56:36 by pcaplat           #+#    #+#             */
/*   Updated: 2026/05/04 14:20:14 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	*gnl_calloc(size_t n, size_t size);
char	*gnl_substr(char **s);
char	*ft_strfdup(char *s, int index);
char	*set_substr(const char *s, int len);
int		ft_strlen_sep(const char *s, char sep);
int		gnl_strchr(const char *s, char c);

#endif
