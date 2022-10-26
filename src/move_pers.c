/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_pers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:17:56 by supersko          #+#    #+#             */
/*   Updated: 2022/10/26 15:21:39 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	f_is_box_crossed(t_player *player)
{
	int	dir;

	dir = 0;
	if (player->pos_box.y > STEPS_PER_BOX)
		dir += N;
	if (player->pos_box.y < 0)
		dir += S;
	if (player->pos_box.x > STEPS_PER_BOX)
		dir += E;
	if (player->pos_box.x < 0)
		dir += W;
	return (dir);
}

/* return 1 if same, 2 if changed boxes, 0 if hit a wall) */
int	check_update_box_pos( t_data *data)
{
	int	has_cross_over;

	has_cross_over = f_is_box_crossed(data->player);
	if (has_cross_over)
	{
		//check_wall
		//
	}
	return (0);
}

void	move_pers( t_data *data, int dir)
{
	t_player	*player;

	if (dir == FORWARD)
	{
		//apply
	}
 	(void) data;
 	(void)player;
 	return ;
 }
 
