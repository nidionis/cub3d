/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_ft.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <ndionis@student.42mulhouse.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 19:31:49 by supersko          #+#    #+#             */
/*   Updated: 2022/11/13 12:54:24 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_lstclear(t_obstacle **lst)
{
	t_obstacle	*next_item;

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

t_obstacle	*ft_lstlast(t_obstacle *lst)
{
	if (!lst)
		return (0);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

t_obstacle	*ft_lstnew(t_rayponse content, char type)
{
	t_obstacle	*new_;

	new_ = (t_obstacle *) malloc(sizeof(t_obstacle));
	if (!new_)
		return (NULL);
	new_->len = content.len;
	new_->hit_point = content.hit_point;
	new_->type = type;
	new_->next = NULL;
	return (new_);
}

void	ft_lstadd_back(t_obstacle **lst, t_obstacle *new_)
{
	t_obstacle	*buff;

	if (new_)
	{
		buff = ft_lstlast(*lst);
		if (!buff)
			*lst = new_;
		else
			buff->next = new_;
	}
}

void	ft_lstadd_front(t_obstacle **lst, t_obstacle *new_)
{
	t_obstacle	*buff;

	if (lst && new_)
	{
		buff = *lst;
		*lst = new_;
		new_->next = buff;
	}
}
