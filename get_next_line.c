/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matt <maquentr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 20:53:48 by matt              #+#    #+#             */
/*   Updated: 2021/01/21 22:40:25 by matt             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		get_next_line(int fd, char **line)
{
	char buf[10 + 1];
	int byte_was_read;
	int retour_ligne;
	char *p_n;

	retour_ligne = 1;
	*line = "\0";
	while (retour_ligne && (byte_was_read = read(fd, buf, 10)))
	{
		buf[byte_was_read] = '\0';
		printf("buf = %s\n", buf);
		if ((p_n = ft_strchr(buf, '\n')))
		{
			//*p_n = '\0';
			retour_ligne = 0;
		}
		*line = ft_strjoin(*line, buf);
		printf("line = %s\n", *line);
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
}
