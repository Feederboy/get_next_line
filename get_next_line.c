/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matt <maquentr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 20:53:48 by matt              #+#    #+#             */
/*   Updated: 2021/01/27 17:01:24 by maquentr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		is_line(char *tmp)
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

static char	*check_static(char *s, char **line)
{
	char *p_n;

	p_n = NULL;
	if (s)
		if ((p_n = ft_strchr(s, '\n')))
		{
			*p_n = '\0';
			*line = ft_strdup(s);
			//if (!(*line))
			//	return (-1);
			if (p_n + 1)
				++p_n;
			ft_strlcpy(s, p_n, ft_strlen(p_n) + 1);
		}
		else
		{
			*line = ft_strdup(s);
			//if (!(*line))
			//	return (NULL);
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

	p_n = NULL;
	if (fd < 0 || BUFFER_SIZE < 1 || !line)
		return (-1);
	p_n = check_static(s[fd], line);
	while (!p_n && (byte_was_read = read(fd, buf, BUFFER_SIZE)))
	{
		if (byte_was_read < 0)
			return (-1);
		buf[byte_was_read] = '\0';
		if (ft_strchr(buf, '\n')) //fais pointer p_n sur buf au niveau du \n
		{
			p_n = ft_strchr(buf, '\n');
			*p_n = '\0'; //supprime le reste de la ligne a partir de l'endroit pointe sur buf (\n)
			if (p_n + 1)
				p_n++; //skip \n
			s[fd] = ft_strdup(p_n);
			if (!s[fd])
				return (-1);
		}
		*line = ft_strjoin(*line, buf);
	}
	if (is_line(s[fd]) > 0)
		return (1);
//	if (s[fd])
//		return (byte_was_read || ft_strlen(s[fd]) || (ft_strlen(*line))) ? 1 : 0; //si rien dans byte et s et line alors fin du game
	else
		return (-1);
}


int main(int ac, char **av)
{
	int fd;
	char *line;
	(void)ac;

	fd = open(av[1], O_RDONLY);
	while (get_next_line(fd, &line))
	{
		printf("line = %s\n", line);
		free(line);
	}
	close(fd);
	return (0);
}

