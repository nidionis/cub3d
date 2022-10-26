/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_pers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <ndionis@student.42mulhouse.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:17:56 by supersko          #+#    #+#             */
/*   Updated: 2022/10/25 20:07:13 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	f_is_box_crossed(t_p *p)
{
	int	dir;

	dir = 0;
	if (p->pos_box.y > STEP_PER_BOX)
		dir += N;
	if (p->pos_box.y < 0)
		dir += S;
	if (p->pos_box.x > STEP_PER_BOX)
		dir += E;
	if (p->pos_box.x < 0)
		dir += W;
	return (dir);
}

/* return 1 if same, 2 if changed boxes, 0 if hit a wall) */
int	check_update_box_pos(t_s *s)
{
	int	has_cross_over;

	has_cross_over = f_is_box_crossed(s->p);
	if (has_cross_over)
	{
		//check_wall
		//
	}
}

void	move_pers(t_s *s, int dir)
{
	t_person	*p;

	if (dir == FORWARD)
	{
		apply
	}
 	(void)s;
 	return ;
 }
 
