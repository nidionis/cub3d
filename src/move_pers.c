/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suplayerko <suplayerko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:17:56 by suplayerko          #+#    #+#             */
/*   Updated: 2022/10/26 17:37:25 by suplayerko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	f_is_box_crossed(t_player *player)
{
	int	direction;

	direction= 0;
	if (player->pos_box.y > STEPS_PER_BOX)
		direction += N;
	if (player->pos_box.y < 0)
		direction += S;
	if (player->pos_box.x > STEPS_PER_BOX)
		direction += E;
	if (player->pos_box.x < 0)
		direction += W;
	return (direction);
}

/* return 1 if same, 2 if changed boxes, 0 if hit a wall) */
int	check_update_box_pos(t_data *data)
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

void	move_player(t_data *data, int direction)
{
	t_player	*player;

	if (direction == FORWARD)
	{
		return ;
		//apply
	}
 	(void) data;
 	(void)player;
 	return ;
 }
 
