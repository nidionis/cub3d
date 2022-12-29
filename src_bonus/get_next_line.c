/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:17:56 by supersko          #+#    #+#             */
/*   Updated: 2022/12/29 14:00:03 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static char	*ft_realloc_cat(char *line, char c, int *len)
{
	char	*returned;
	int		i;

	i = 0;
	returned = malloc(*len + 2);
	if (!returned)
		return (NULL);
	while (i < *len && line)
	{
		returned[i] = line[i];
		i++;
	}
	returned[*len] = c;
	returned[++(*len)] = '\0';
	if (line)
		free(line);
	return (returned);
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
