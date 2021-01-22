/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matt <maquentr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 20:53:48 by matt              #+#    #+#             */
/*   Updated: 2021/01/22 15:40:37 by maquentr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	**check_static(char *s, char **line)
{
	if (s)
		*line = ft_strdup(s);
	else
		*line = "\0";
	return (line);
}
int		get_next_line(int fd, char **line)
{
	static char *s;
	char buf[BUFFER_SIZE + 1];
	int byte_was_read;
	int retour_ligne;
	char *p_n;
	
	retour_ligne = 1;
	
	check_static(s, line);
	while (retour_ligne && (byte_was_read = read(fd, buf, BUFFER_SIZE)))
	{
		buf[byte_was_read] = '\0';
		if ((p_n = ft_strchr(buf, '\n'))) //fais pointer p_n sur buf au niveau du \n
		{
			s = p_n + 1; //stocke le reste apres la ligne dans s, sans le \n
			printf("s = %s FIN\n", s);
			*p_n = '\0'; //supprime le reste de la ligne a partir de l'endroit pointe (au \n)
			retour_ligne = 0; //sort de la boucle car \n rencontre
		}
		*line = ft_strjoin(*line, buf);
	}
	return (0);
}

int main()
{
	char *line;
	int fd;
	
	fd = open("test.txt", O_RDONLY);
	get_next_line(fd, &line);
	printf("%s\n", line);
	get_next_line(fd, &line);
	printf("%s\n", line);
	get_next_line(fd, &line);
	printf("%s\n", line);
}
