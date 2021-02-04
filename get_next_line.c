/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matt <maquentr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 20:53:48 by matt              #+#    #+#             */
/*   Updated: 2021/02/04 17:14:15 by matt             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	int		is_line(char *tmp)
{
	int	i;

	i = -1;
	if (!tmp)
		return (-1);
	while (tmp[++i])
		if (tmp[i] == '\n')
			return (1);
	return (0);
}

static char		*check_static(char *s, char **line)
{
	char *p_n;

	p_n = NULL;
	if (s)
		if ((p_n = ft_strchr(s, '\n')))
		{
			*p_n = '\0';
			if (!(*line = ft_strdup(s)))
				return (NULL);
			++p_n;
			ft_strlcpy(s, p_n, ft_strlen(p_n) + 1);
		}
		else
		{
			if (!(*line = ft_strdup(s)))
				return (NULL);
			s = "\0";
		}
	else
	{
		if (!(*line = malloc(sizeof(char) * 1)))
			return (NULL);
		(*line)[0] = '\0';
	}
	return (p_n);
}

static	int		check_end(char **s, char **line, int byte_was_read)
{
	if ((is_line(*s) > 0 || is_line(*line) > 0) || byte_was_read != 0)
		return (1);
	else
		return (0);
}

static int		free_if_newline(char **s, char **p_n)
{
	**p_n = '\0';
	++(*p_n);
	free(*s);
	if (!(*s = ft_strdup(*p_n)))
		return (-1);
	else
		return (1);
}

int				get_next_line(int fd, char **line)
{
	static char		*s[2000];
	char			buf[BUFFER_SIZE + 1];
	int				byte_was_read;
	char			*p_n;

	if (fd < 0 || BUFFER_SIZE < 1 || !line)
		return (-1);
	p_n = check_static(s[fd], line);
	while (!p_n && (byte_was_read = read(fd, buf, BUFFER_SIZE)))
	{
		if (byte_was_read < 0)
		{
			free(*line);
			*line = NULL;
			return (-1);
		}
		buf[byte_was_read] = '\0';
		if ((p_n = ft_strchr(buf, '\n')))
			free_if_newline(&s[fd], &p_n);
		free(*line);
		if (!(*line = ft_strjoin(*line, buf)))
			return (-1);
	}
	return (check_end(&s[fd], line, byte_was_read));
}
