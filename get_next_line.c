/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matt <maquentr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 17:27:16 by matt              #+#    #+#             */
/*   Updated: 2021/05/10 17:27:24 by matt             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		check_next_line(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int		find_next_line(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (0);
}

void	save(char **s, char **line)
{
	if (check_next_line(*s) == 1)
	{
		*line = ft_substr(*s, 0, find_next_line(*s), 0);
		*s = ft_substr(*s, find_next_line(*s) + 1, ft_strlen(*s), 1);
	}
	else
	{
		*line = ft_substr((*s), 0, ft_strlen(*s), 1);
		*s = NULL;
	}
}

int		get_next_line(int fd, char **line)
{
	static char	*s[65535];
	char		buffer[BUFFER_SIZE + 1];
	int			byte_read;

	byte_read = 1;
	if (fd < 0 || BUFFER_SIZE <= 0 || !line)
		return (-1);
	while (check_next_line(s[fd]) != 1 && byte_read != 0)
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read == -1)
			return (-1);
		buffer[byte_read] = '\0';
		s[fd] = ft_strjoin(s[fd], buffer);
	}
	save(&s[fd], line);
	if (byte_read == 0 && s[fd] == NULL)
		return (0);
	else
		return (1);
}
