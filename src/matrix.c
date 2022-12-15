/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:17:56 by suplayerko        #+#    #+#             */
/*   Updated: 2022/12/15 03:45:02 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* used for importing map */
char	**ft_append_tab(char **matrix, char *str)
{
	int		tab_len;
	char	**new_tab;

	if (!str)
		return (matrix);
	tab_len = 0;
	if (matrix && *matrix)
	{
		while (matrix[tab_len])
			tab_len++;
	}
	new_tab = malloc((tab_len + 2) * sizeof(char *));
	tab_len += 1;
	if (!new_tab)
	{
		error_msg("[ft_append_tab] did not malloc");
		exit(-1);
	}
	new_tab[tab_len] = NULL;
	tab_len -= 1;
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
