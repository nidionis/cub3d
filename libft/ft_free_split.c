/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <ndionis@student.42mulhouse.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 19:13:11 by supersko          #+#    #+#             */
/*   Updated: 2022/06/01 12:47:55 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_split(char ***tab)
{
	int	i;

	i = 0;
	if (*tab)
	{
		while ((*tab)[i])
		{
			free((*tab)[i]);
			(*tab)[i] = NULL;
			i++;
		}
	}
	free(*tab);
	*tab = NULL;
}
