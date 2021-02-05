/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maquentr <maquentr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 16:42:12 by maquentr          #+#    #+#             */
/*   Updated: 2021/02/05 13:40:35 by matt             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static	int		check_end(char **s, char **line, int byte_was_read, int fd)
{
	if (byte_was_read < 0)
	{
		free(*line);
		*line = NULL;
		return (-1);
	}
	else if (byte_was_read == 0 && !s[fd])
		return (0);
	else
		return (1);
}

static int		free_if_newline(char **s, char **line)
{
	char	*tmp;
	int		i;

	i = 0;
	while ((*s)[i] != '\n' && (*s)[i] != '\0')
		i++;
	if ((*s)[i] == '\n')
	{
		*line = ft_substr(*s, 0, i);
		tmp = ft_strdup(&((*s)[i + 1]));
		free(*s);
		*s = tmp;
		if ((*s)[0] == '\0')
		{
			free(*s);
			*s = NULL;
		}
	}
	else
	{
		*line = ft_strdup(*s);
		free(*s);
		*s = NULL;
	}
	return (1);
}

int				get_next_line(int fd, char **line)
{
	static char		*s[2000];
	char			buf[BUFFER_SIZE + 1];
	int				byte_was_read;
	char			*p_n;

	if (fd < 0 || !line)
		return (-1);
	while ((byte_was_read = read(fd, buf, BUFFER_SIZE)))
	{
		buf[byte_was_read] = '\0';
		if (!s[fd])
			s[fd] = ft_strdup(buf);
		else
		{
			p_n = ft_strjoin(s[fd], buf);
			free(s[fd]);
			s[fd] = p_n;
		}
		if (ft_strchr(buf, '\n'))
			break ;
	}
	free_if_newline(&s[fd], line);
	return (check_end(s, line, byte_was_read, fd));
}
