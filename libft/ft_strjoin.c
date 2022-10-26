/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:51:11 by supersko          #+#    #+#             */
/*   Updated: 2022/10/26 15:48:59 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t			len_s1;
	unsigned int	ii;
	char			*returned;

	if (!s1)
		return (NULL);
	ii = 0;
	len_s1 = ft_strlen((char *) s1);
	returned = (char *) malloc(sizeof(char) * (ft_strlen((char *) s2) + len_s1 + 1));
	if (!returned)
		return (NULL);
	ii = 0;
	while (ii < len_s1)
	{
		returned[ii] = s1[ii];
		ii++;
	}
	while (s2[ii - len_s1])
	{
		returned[ii] = s2[ii - len_s1];
		ii++;
	}
	returned[ii] = '\0';
	return (returned);
}

/*
//
#include <stdio.h>
#include <string.h>
#include "libft.h"
// MAIN
int main(void)
{
	char s1[1000];
	char s2[1000];
	char *verif;

	strcpy(s1, "ch1 ");
	strcpy(s2, "ch2");
	verif = ft_strjoin(s1, s2);
	if (ft_strncmp(verif, "ch1 et ch2", 20))
	{
		printf("Pb at ft_strjoin\n");
	}
	free(verif);
}
*/
