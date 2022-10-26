/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 19:17:07 by supersko          #+#    #+#             */
/*   Updated: 2022/10/26 15:48:59 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen(int n)
{
	int	len;

	len = 0;
	if (n < 0)
	{
		n *= -1;
		len++;
	}
	while (n > 9)
	{
		n /= 10;
		len++;
	}
	return (++len);
}

static char	*my_loc(int len)
{
	char	*returned;

	returned = (char *) malloc(sizeof(char) * (len + 1));
	if (!returned)
		return (NULL);
	returned[len] = '\0';
	return (returned);
}

static void	make_str(int *n, char *n_str, int i)
{
	while (i--)
	{
		*(n_str + i) = (char)(*n % 10) + '0';
		*n /= 10;
	}
}

static char	*carry_negative(int *n, char *n_strn, int *len)
{
	if (*n < 0)
	{
		*(n_strn++) = '-';
		(*len)--;
		*n *= -1;
	}
	return (n_strn);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*returned;
	char	*num;

	len = ft_intlen(n);
	returned = my_loc(len);
	if (!returned)
		return (NULL);
	num = returned;
	if (n == -2147483648)
	{
		ft_strlcpy(returned, "-2147483648", 12);
		return (returned);
	}
	num = carry_negative(&n, num, &len);
	make_str(&n, num, len);
	return (returned);
}

/*
//
#include <stdio.h>
// MAIN
int main(void)
{
	char	*strnb;

	strnb = ft_itoa(-123);
	printf("%s\n", strnb);
	free(strnb);

	strnb = ft_itoa(-0);
	printf("%s\n", strnb);
	free(strnb);

	strnb = ft_itoa(1230);
	printf("%s\n", strnb);
	free(strnb);
}
*/
