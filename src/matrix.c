/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <ndionis@student.42mulhouse.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:17:56 by supersko          #+#    #+#             */
/*   Updated: 2022/10/26 12:19:55 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**ft_append_tab(char **matrix, char *str)
{
	int		tab_len;
	char	**new_tab;

	if (!str)
		return (matrix);
	tab_len = 0;
	if (matrix)
		while (matrix[tab_len])
			tab_len++;
	new_tab = malloc((tab_len++ + 2) * sizeof(char *));
	if (!new_tab)
		return (NULL);
	new_tab[tab_len--] = NULL;
	new_tab[tab_len] = str;
	while (tab_len--)
		new_tab[tab_len] = matrix[tab_len];
	free(matrix);
	matrix = NULL;
	return (new_tab);
}

int	ft_matrixlen(char **matrix)
{
	int	len;

	len = 0;
	if (matrix)
	{
		while (matrix[len])
			len++;
	}
	return (len);
}

void	print_tab(char **tab)
{
	while (*tab)
		fprintf(stderr, "%s\n", *tab++);
}

char	**default_map(char	*argv[])
{
	char	**map;
	char	*line;
	int		fd;

	map = NULL;
	if (argv[1])
		fd = open(argv[1], O_RDONLY);
	else
		fd = open("test.cub", O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		map = ft_append_tab(map, line);
		line = get_next_line(fd);
	}
	return (map);
}
