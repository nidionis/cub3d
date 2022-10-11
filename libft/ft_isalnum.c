/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <ndionis@student.42mulhouse.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:48:16 by supersko          #+#    #+#             */
/*   Updated: 2022/03/11 17:56:15 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= (int) 'A' && c <= (int) 'Z') || \
		(c >= (int) 'a' && c <= (int) 'z') || \
		(c >= '0' && c <= '9'))
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
int	main(int argc, char *argv[])
{
	int	ii;

	ii = -1;
	while (ii < 257)
	{
		if (isalnum(ii) != ft_isalnum(ii))
		{
			printf("isalnum(%c) = %d\n", (char)ii, isalnum(ii));
			printf("ft_isalnum(%c) = %d\n", (char)ii, ft_isalnum(ii));
			return (error_msg(ii, "isalnum"));
		}
		ii++;
	}
	(void)argc;
	printf("%s have same output from same input\n", argv[0]);
	return (0);
}
*/
