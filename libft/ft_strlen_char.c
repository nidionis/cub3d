/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <ndionis@student.42mulhouse.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 14:29:28 by supersko          #+#    #+#             */
/*   Updated: 2022/04/21 15:18:06 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_char(char *str, char sep)
{
	size_t	len;

	len = 0;
	if (str)
	{
		while (*str && *str++ != sep)
			len++;
	}
	return (len);
}

/*
#include <stdio.h>
int main()
{
	printf("%zu\n", ft_strlen_char(NULL, 0));
	printf("%zu\n", ft_strlen_char("a", ' '));
	printf("%zu\n", ft_strlen_char(" a", ' '));
	printf("%zu\n", ft_strlen_char("a ", ' '));
	printf("%zu\n", ft_strlen_char(" a ", ' '));
	printf("%zu\n", ft_strlen_char("a a", ' '));
	printf("%zu\n", ft_strlen_char("a a ", ' '));
	printf("%zu\n", ft_strlen_char(" a a", ' '));
	printf("%zu\n", ft_strlen_char(" a a ", ' '));
}

*/
