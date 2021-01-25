/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matt <maquentr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 20:53:48 by matt              #+#    #+#             */
/*   Updated: 2021/01/25 20:28:46 by matt             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*check_static(char *s, char **line)
{
	char *p_n;

	p_n = NULL;
	if (s)
		if ((p_n = ft_strchr(s, '\n')))
		{
			*p_n = '\0';
			*line = ft_strdup(s);
			if (p_n + 1)
				++p_n;
			ft_strlcpy(s, p_n, ft_strlen(p_n) + 1);
		}
		else
		{
			*line = ft_strdup(s);
			s = "\0";
		}
	else
	{
		if (!(*line = malloc(sizeof(char) * 1)))
			return (NULL);
		line[0] = "\0";
	}
	return (p_n);
}

int		get_next_line(int fd, char **line)
{
	static char *s[2000];
	char buf[BUFFER_SIZE + 1];
	int byte_was_read;
	char *p_n;
	
	if (fd < 0 || BUFFER_SIZE < 1 || !line)
		return (-1);
	p_n = check_static(s[fd], line);
	while (!p_n && (byte_was_read = read(fd, buf, BUFFER_SIZE)))
	{
		buf[byte_was_read] = '\0';
		if ((p_n = ft_strchr(buf, '\n'))) //fais pointer p_n sur buf au niveau du \n
		{
			*p_n = '\0'; //supprime le reste de la ligne a partir de l'endroit pointe sur buf (\n)
			if (p_n + 1)
				p_n++; //skip \n
			free(s[fd]);
			s[fd] = ft_strdup(p_n);
		}
			*line = ft_strjoin(*line, buf);
	}
	return (byte_was_read || ft_strlen(s[fd]) || ft_strlen(*line)) ? 1 : 0; //si rien dans byte et s et line alors fin du game
}

int main()
{
	char *line;
	char *line2;
	int fd;
	int fd2;

	fd2 = open("ntm.txt", O_RDONLY);
	fd = open("test.txt", O_RDONLY);
	while (get_next_line(fd, &line) || get_next_line(fd2, &line2))
	{
		printf("main = %s\n\n", line);
		printf("main2 = %s\n\n", line2);
		free(line);
		free(line2);
		line = NULL;
		line2 = NULL;
	}
	return (0);
}
