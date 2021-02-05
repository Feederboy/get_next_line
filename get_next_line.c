/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matt <maquentr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 20:53:48 by matt              #+#    #+#             */
/*   Updated: 2021/02/05 13:25:34 by matt             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	char *tmp;
	int i;

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

int	main(void) {
	int		fd = -1;
	char	*line =	NULL;
	int		ret;

	/* open file - if an error occurs here, the test will be ignored, that's not your fault ! */
	if ((fd = open("empty_lines.txt", O_RDONLY)) == -1 || read(fd, NULL, 0) == -1) {
		return (-1);
	}

	while ((ret = get_next_line(fd, &line)) > 0) {
		printf("%s\n", line);
		free(line);
		line = NULL;
	}
	printf("return value: %d\n", ret);
	free(line);

	/* cleaning up */
	close(fd);

	return (0);
}
