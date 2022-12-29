/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pos_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suplayerko <suplayerko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:17:56 by suplayerko          #+#    #+#             */
/*   Updated: 2022/11/19 17:45:22 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_point	update_pos_in_step(t_player *player)
{
	t_point	pos_in_step;
	int		s_p_b;
	int		u;

	s_p_b = (int)STEPS_PER_BOX;
	u = (int)UNITS_PER_BOX;
	pos_in_step.x = player->pos_map.x * s_p_b + player->pos_box.x * s_p_b / u;
	pos_in_step.y = player->pos_map.y * s_p_b + player->pos_box.y * s_p_b / u;
	player->pos_in_step = pos_in_step;
	if (pos_in_step.x < 0 || pos_in_step.y < 0)
		error_msg("[update_pos_in_step] pos_in_step probably overflow");
	return (pos_in_step);
}

t_point	update_pos_in_pix(t_player *player)
{
	t_point	pos_in_pix;
	int		u;

	u = (int)UNITS_PER_BOX;
	pos_in_pix.x = player->pos_map.x * u + player->pos_box.x;
	pos_in_pix.y = player->pos_map.y * u + player->pos_box.y;
	if (pos_in_pix.x < 0 || pos_in_pix.y < 0)
		error_msg("[update_pos_in_step] pos_in_step probably overflow");
	player->pos_in_pix = pos_in_pix;
	return (pos_in_pix);
}
