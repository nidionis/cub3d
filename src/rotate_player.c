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

void	rotate_player(t_player *player, int move)
{
	double	radian_angle;

	radian_angle = (double)DEFAULT_ROTATION_ANGLE;
	if (move == RIGHT)
		radian_angle *= -1.00000;
	else if (move != LEFT)
		error_msg("[rotate_player] wrong instruction");
	rotate_vector(&player->direction, radian_angle);
}
