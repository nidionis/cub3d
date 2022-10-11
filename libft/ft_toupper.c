/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <ndionis@student.42mulhouse.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:48:16 by supersko          #+#    #+#             */
/*   Updated: 2022/03/11 18:37:17 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= (int) 'a' && c <= (int) 'z')
		return (c - 32);
	else
		return (c);
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
		if (toupper(ii) != ft_toupper(ii))
		{
			printf("toupper(%c) = %d\n", (char)ii, toupper(ii));
			printf("ft_toupper(%c) = %d\n", (char)ii, ft_toupper(ii));
			return (error_msg(ii, "toupper"));
		}
		ii++;
	}
	printf("You r da man ;)\n");
	return (0);
}
*/
