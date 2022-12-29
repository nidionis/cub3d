/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 17:21:34 by supersko          #+#    #+#             */
/*   Updated: 2022/12/29 14:01:14 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	rotate_player(t_player *player, int move)
{
	double	radian_angle;
	double	speed;

	speed = 0.10000;
	radian_angle = (double)DEFAULT_ROTATION_ANGLE;
	if (move == LEFT)
		radian_angle -= speed;
	else if (move != RIGHT)
		error_msg("[rotate_player] wrong instruction");
	else
		radian_angle -= (speed -0.07200);
	rotate_vector(&player->direction, radian_angle);
}
