/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <ndionis@student.42mulhouse.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:48:16 by supersko          #+#    #+#             */
/*   Updated: 2022/03/11 17:56:34 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= (int) 'A' && c <= (int) 'Z') || \
		(c >= (int) 'a' && c <= (int) 'z'))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}
/*
//
#include "error_msg.h"
#include <ctype.h>
#include <stdio.h>
// MAIN
int	main(void)
{
	int	ii;

	ii = -1;
	while (ii < 257)
	{
		if (isalpha(ii) != ft_isalpha(ii))
		{
			printf("isalpha(%c) = %d\n", (char)ii, isalpha(ii));
			printf("ft_isalpha(%c) = %d\n", (char)ii, ft_isalpha(ii));
			return (error_msg(ii, "isalpha"));
		}
		ii++;
	}
	return (0);
}
*/
