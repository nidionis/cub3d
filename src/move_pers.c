/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_pers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:17:56 by supersko          #+#    #+#             */
/*   Updated: 2022/10/26 15:09:41 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	f_is_box_crossed(t_person *p)
{
	int	dir;

	dir = 0;
	if (p->pos_box.y > STEPS_PER_BOX)
		dir += N;
	if (p->pos_box.y < 0)
		dir += S;
	if (p->pos_box.x > STEPS_PER_BOX)
		dir += E;
	if (p->pos_box.x < 0)
		dir += W;
	return (dir);
}

/* return 1 if same, 2 if changed boxes, 0 if hit a wall) */
int	check_update_box_pos( t_data *data)
{
	int	has_cross_over;

	has_cross_over = f_is_box_crossed(data->p);
	if (has_cross_over)
	{
		//check_wall
		//
	}
	return (0);
}

void	move_pers( t_data *data, int dir)
{
	t_person	*p;

	if (dir == FORWARD)
	{
		//apply
	}
 	(void) data;
 	(void)p;
 	return ;
 }
 
