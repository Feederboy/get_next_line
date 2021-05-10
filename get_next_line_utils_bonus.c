/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matt <maquentr@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 17:28:41 by matt              #+#    #+#             */
/*   Updated: 2021/05/10 17:28:43 by matt             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (!(str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	if (s1)
	{
		while (s1[i] && s1)
		{
			str[i] = s1[i];
			i++;
		}
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	free(s1);
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, int len, int f)
{
	char	*res;
	int		i;

	i = 0;
	if ((int)start >= ft_strlen((char *)s))
	{
		if (!(res = malloc(sizeof(char) * 1)))
			return (NULL);
		free((char *)s);
		res[0] = '\0';
		return (res);
	}
	if (!(res = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (i < len && s[start])
		res[i++] = s[start++];
	res[i] = '\0';
	if (f == 1)
		free((char *)s);
	return (res);
}
