/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:51:11 by supersko          #+#    #+#             */
/*   Updated: 2022/10/26 15:48:59 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str0, int c, size_t n)
{
	size_t			ii;
	unsigned char	*str;

	str = (unsigned char *) str0;
	ii = 0;
	while (ii < n)
	{
		if (*(str + ii) == (unsigned char)c)
			return ((void *)str + ii);
		ii++;
	}
	return (NULL);
}

/*
//
#include "error_msg.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
// MAIN
int test_memchr(char *str, char c)
{
	unsigned int	returned;
	int				ii;

	ii = 0;
	while (ii < 5)
	{
		returned = memchr(str, c, ii) - ft_memchr(str, c, ii);
		if (returned)
		{
			printf("[bug] at str: %s, c: %c, n = %d\n", str, c, ii);
			return (1);
		}
		ii++;
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	int ii = 0;
	test_memchr("abcbi", 'b');
	test_memchr("abc", '\0');
	test_memchr("", 'a');
	test_memchr("", '\0');
	printf("test finished\n");
}
*/
