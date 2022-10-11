/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wd_count.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <ndionis@student.42mulhouse.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 13:09:34 by supersko          #+#    #+#             */
/*   Updated: 2022/04/21 15:53:23 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_wd_count(char *str, char sep)
{
	int		wd_nb;

	wd_nb = 0;
	if (str)
	{
		while (*str == sep)
			str++;
		while (*str)
		{
			str = ft_get_next_wd(str, sep);
			if (str != NULL)
				wd_nb++;
		}
	}
	else
		error_msg("str == NULL in wc str");
	return (wd_nb);
}

/*
#include <stdio.h>
int main()
{
	printf("%d\n", ft_wd_count(NULL, 0));
	printf("%d\n", ft_wd_count("a", ' '));
	printf("%d\n", ft_wd_count(" a", ' '));
	printf("%d\n", ft_wd_count("a ", ' '));
	printf("%d\n", ft_wd_count(" a ", ' '));
	printf("%d\n", ft_wd_count("a a", ' '));
	printf("%d\n", ft_wd_count("a a ", ' '));
	printf("%d\n", ft_wd_count(" a a", ' '));
	printf("%d\n", ft_wd_count(" a a ", ' '));
}
*/
