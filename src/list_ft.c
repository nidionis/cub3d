/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <ndionis@student.42mulhouse.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 19:31:49 by supersko          #+#    #+#             */
/*   Updated: 2022/03/11 20:40:51 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_lstclear(t_raysponse **lst)
{
	t_raysponse	*next_item;

	if (lst)
	{
		while (*lst)
		{
			next_item = (*lst)->next;
			free(*lst);
			*lst = next_item;
		}
	}
}

t_raysponse	*ft_lstlast(t_raysponse *lst)
{
	if (!lst)
		return (0);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}


t_raysponse	*ft_lstnew(void *content)
{
	t_raysponse	*new;

	new = (t_raysponse *) malloc(sizeof(t_raysponse));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back(t_raysponse **lst, t_raysponse *new)
{
	t_raysponse	*buff;

	if (new)
	{
		buff = ft_lstlast(*lst);
		if (!buff)
			*lst = new;
		else
			buff->next = new;
	}
}
