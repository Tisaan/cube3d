/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>		        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 21:30:04 by tseche            #+#    #+#             */
/*   Updated: 2024/10/29 22:54:00 by tseche	          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_file(int fd, char *line, char *buff)
{
	int		nb_read;
	char	*temp;

	nb_read = 1;
	while (nb_read > 0)
	{
		nb_read = read(fd, buff, BUFFER_SIZE);
		if (nb_read == -1)
		{
			free(line);
			return (NULL);
		}
		else if (nb_read == 0)
			break ;
		buff[nb_read] = '\0';
		if (!line)
			line = ft_strdup("");
		temp = line;
		line = ft_strjoin(temp, buff);
		free(temp);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	return (line);
}

char	*rm_line(char *ret)
{
	int		i;
	char	*line;

	i = 0;
	while (ret[i] != '\n' && ret[i] != '\0')
		i++;
	if (ret[i] == '\0')
		return (NULL);
	line = ft_substr(ret, i + 1, ft_strlen(ret) - i);
	if (!*line)
	{
		free(line);
		return (NULL);
	}
	ret[i + 1] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*line[1024];
	char		*ret;
	char		*buff;

	buff = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	ret = read_file(fd, line[fd], buff);
	free(buff);
	if (!ret)
		return (NULL);
	line[fd] = rm_line(ret);
	return (ret);
}
