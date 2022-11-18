/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suplayerko <suplayerko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:17:56 by suplayerko          #+#    #+#             */
/*   Updated: 2022/11/13 16:14:47 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_obstacle	*add_obstacle(t_data *data, t_rayponse r, char m_case, t_obstacle **ls)
{
	t_obstacle		*obstacle;

	obstacle = ft_lstnew(r, m_case);
	if (!obstacle)
		clean_exit(data, -1);
	if (m_case == SPRITE)
	{
		obstacle->side = -1;
		obstacle->hit_point.x = -1;
		obstacle->hit_point.y = -1;
	}
	else
	{
		obstacle->sprite_hit = -1;
		obstacle->sprite_pointer = NULL;
	}
	ft_lstadd_front(ls, obstacle);
	return (obstacle);
}

t_obstacle	*insert_sort_obstacle(t_obstacle **ls, t_obstacle *new_itm)
{
	t_obstacle	*tmp;
	t_obstacle	*last_tmp;

	last_tmp = NULL;
	if (!*ls)
		*ls = new_itm;
	else if (new_itm)
	{
		tmp = *ls;
		while (tmp && new_itm->len < tmp->len)
		{
			last_tmp = tmp;
			tmp = tmp->next;
		}
		new_itm->next = tmp;
		if (last_tmp)
			last_tmp->next = new_itm;
		else
			*ls = new_itm;
	}
	return (*ls);
}

t_obstacle	*sort_obstacles(t_obstacle **ls)
{
	t_obstacle	*new_list;
	t_obstacle	*tmp;
	t_obstacle	*next_tmp;

	new_list = NULL;
	tmp = *ls;
	if (ls && *ls)
	{
		while (tmp)
		{
			next_tmp = tmp->next;
			insert_sort_obstacle(&new_list, tmp);
			tmp = next_tmp;
		}
	}
	*ls = new_list;
	return (new_list);
}

void	convert_pos_and_dir_to_line(t_point pos, t_vector vec, t_vector line[2])
{
	t_vector	v_pos;

	v_pos.x = (double)pos.x;
	v_pos.y = (double)pos.y;
	line[0] = v_pos;
	translate_vector_as_pt(vec, &v_pos);
	line[1] = v_pos;
}