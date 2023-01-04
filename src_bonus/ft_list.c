/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 13:59:44 by dpaulino          #+#    #+#             */
/*   Updated: 2023/01/04 15:53:19 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub3d_bonus.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*buff;

	if (new)
	{
		buff = ft_lstlast(*lst);
		if (!buff)
			*lst = new;
		else
			buff->next = new;
	}
}

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	t_list	*buff;

	if (lst && new)
	{
		buff = *lst;
		*lst = new;
		new->next = buff;
	}
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next_item;

	if (lst && del)
	{
		while (*lst)
		{
			next_item = (*lst)->next;
			ft_lstdelone(&(*lst), del);
			*lst = next_item;
		}
	}
	*lst = NULL;
}

void	ft_lstdelone(t_list **lst, void (*del)(void *))
{
	if (lst && *lst != NULL)
	{
		if ((*lst)->content)
		{
			del((*lst)->content);
			(*lst)->content = NULL;
		}
		*lst = NULL;
	}
}
