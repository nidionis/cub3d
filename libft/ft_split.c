/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 16:31:55 by supersko          #+#    #+#             */
/*   Updated: 2022/10/26 15:48:59 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**make_tab(char **returned, char const *s, char c, unsigned int nb_wd)
{
	size_t	i_wd;
	size_t	wd_len;

	i_wd = 0;
	while (i_wd < nb_wd)
	{
		while (*s == c)
			s++;
		wd_len = ft_strlen_char((char *)s, c);
		if (wd_len != 0)
		{
			returned[i_wd] = (char *) malloc(sizeof(char) * (wd_len + 1));
			if (!returned[i_wd])
				return (NULL);
		}
		ft_strlcpy(returned[i_wd], s, wd_len + 1);
		returned[i_wd][wd_len] = '\0';
		s += wd_len;
		i_wd++;
	}
	return (returned);
}

char	**ft_split(char const *s, char c)
{
	char			**returned;
	unsigned int	nb_wd;

	if (!s)
		return (NULL);
	nb_wd = ft_wd_count((char *) s, c);
	returned = (char **) malloc((nb_wd + 1) * sizeof(char *));
	if (!returned)
		return (NULL);
	returned = make_tab(returned, s, c, nb_wd);
	returned[nb_wd] = NULL;
	return (returned);
}

/*
//
#include <string.h>
#include <stdio.h>
// MAIN

void put_header(void)
{
	printf("****************************************************\n");
}

int main(void)
{
	char	**sortie;
	int		ii;

	put_header();
	sortie = ft_split("Phrase de      test", ' ');
	ii = 0;
	while (sortie[ii] != NULL)
		 printf("%s\n", sortie[ii++]); 

	put_header();
	sortie = ft_split("P", ' ');
	ii = 0;
	while (sortie[ii] != NULL)
		 printf("%s\n", sortie[ii++]); 

	put_header();
	sortie = ft_split("", ' ');
	ii = 0;
	while (sortie[ii] != NULL)
		 printf("%s\n", sortie[ii++]); 

	put_header();
	sortie = ft_split(" a ", ' ');
	ii = 0;
	while (sortie[ii] != NULL)
		 printf("%s\n", sortie[ii++]); 

	put_header();
	sortie = ft_split(" a", ' ');
	ii = 0;
	while (sortie[ii] != NULL)
		 printf("%s\n", sortie[ii++]); 

	put_header();
	sortie = ft_split("a ", ' ');
	ii = 0;
	while (sortie[ii] != NULL)
		 printf("%s\n", sortie[ii++]); 

	put_header();
	ii = 0;
	while (sortie[ii] != NULL)
		 printf("%s\n", sortie[ii++]); 
		 printf("+++++++++"); 
}
	char s[10];
	strcpy(s, "");
	printf("for [%s] -> %d\n", s, _count(s, ' '));
	strcpy(s, "  ");
	printf("for [%s] -> %d\n", s, _count(s, ' '));
	strcpy(s, "a");
	printf("for [%s] -> %d\n", s, _count(s, ' '));
	strcpy(s, "a ");
	printf("for [%s] -> %d\n", s, _count(s, ' '));
	strcpy(s, " a");
	printf("for [%s] -> %d\n", s, _count(s, ' '));
	strcpy(s, " a ");
	printf("for [%s] -> %d\n", s, _count(s, ' '));
	strcpy(s, "  aa  ");
	printf("for [%s] -> %d\n", s, _count(s, ' '));
	strcpy(s, "bb   bb");
	printf("for [%s] -> %d\n", s, _count(s, ' '));
}
*/
