/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <ndionis@student.42mulhouse.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:17:56 by supersko          #+#    #+#             */
/*   Updated: 2022/04/07 16:31:11 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*ft_realloc_cat(char *line, char c, int *len)
{
	char	*ret;
	int		i;

	i = 0;
	ret = (char *) malloc(*len + 2);
	if (!ret)
		return (NULL);
	while (i < *len && line)
	{
		ret[i] = line[i];
		i++;
	}
	ret[*len] = c;
	ret[++(*len)] = '\0';
	if (line)
		free(line);
	return (ret);
}

char	*get_next_line(int fd)
{
	char	c;
	char	*line;
	int		len;

	len = 0;
	line = NULL;
	while (1)
	{
		if (read(fd, &c, 1) > 0)
			line = ft_realloc_cat(line, c, &len);
		else
			(c = '\0');
		if (c == '\n' || !c)
			return (line);
	}
	return (NULL);
}
