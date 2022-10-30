/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suplayerko <suplayerko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:17:56 by suplayerko          #+#    #+#             */
/*   Updated: 2022/10/26 16:24:32 by suplayerko         ###   ########.fr       */
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
