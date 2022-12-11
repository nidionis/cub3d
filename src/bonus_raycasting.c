/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 17:25:15 by supersko          #+#    #+#             */
/*   Updated: 2022/12/01 17:56:02 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_list	*closest_in_list(t_list **lst)
{
	t_list		*tmp;
	t_list		*l_closest;
	double		closest;
	t_obstacle	*closest_s;

	tmp = *lst;
	l_closest = tmp;
	closest_s = (t_obstacle *)(tmp->content);
	closest = closest_s->dist;
	while (tmp)
	{
		closest_s = (t_obstacle *)(tmp->content);
		if (closest > closest_s->dist)
		{
			closest = closest_s->dist;
			l_closest = tmp;
		}
		tmp = tmp->next;
	}
	return (l_closest);
}

static void	pop_closest(t_list **lst, t_list *closest)
{
	t_list	*tmp;

	tmp = *lst;
	if (tmp == closest)
	{
		*lst = NULL;
		return ;
	}
	while (tmp)
	{
		if (tmp->next == closest)
		{
			tmp->next = closest->next;
			break ;
		}
		tmp = tmp->next;
	}
}

t_list	*sort_obstacles(t_list **lst)
{
	t_list	*sorted_list;
	t_list	*list;
	t_list	*closest;

	sorted_list = NULL;
	list = *lst;
	while (list)
	{
		closest = closest_in_list(&list);
		pop_closest(&list, closest);
		ft_lstadd_front(&sorted_list, closest);
	}
	*lst = sorted_list;
	return (list);
}

/* must be used in a sorted list
 * cut the head of the list until the distance is behing the wall
 * */
void	clean_obstacle_behind_wall(t_list **list, double distance_max)
{
	t_list		*tmp;
	t_list		*last_tmp;
	t_list		*list_cpy;
	double		distance;

	list_cpy = *list;
	tmp = *list;
	last_tmp = NULL;
	while (tmp)
	{
		distance = ((t_obstacle *)(tmp->content))->dist;
		if (distance < distance_max)
			break ;
		last_tmp = tmp;
		tmp = tmp->next;
	}
	*list = tmp;
	if (last_tmp)
	{
		last_tmp->next = NULL;
		ft_lstclear(&list_cpy, free);
	}
}
