/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suplayerko <suplayerko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:17:56 by suplayerko          #+#    #+#             */
/*   Updated: 2022/10/26 17:33:57 by suplayerko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_point	pix_pos_in_box(t_point pos_box)
{
	t_point	pos_in_pix;

	pos_in_pix.x = (((double)pos_box.x / (double)STEPS_PER_BOX) * (double)UNITS_PER_BOX);
	pos_in_pix.y = (((double)pos_box.y / (double)STEPS_PER_BOX) * (double)UNITS_PER_BOX);
	return (pos_in_pix);
}

t_point	update_pos_in_step(t_player *player)
{
	t_point	pos_in_step;

	pos_in_step.x = player->pos_map.x * (int)STEPS_PER_BOX + player->pos_box.x;
	pos_in_step.y = player->pos_map.y * (int)STEPS_PER_BOX + player->pos_box.y;
	player->pos_in_step = pos_in_step;
	if (pos_in_step.x < 0 || pos_in_step.y < 0)
		error_msg("[update_pos_in_step] pos_in_step probably overflow");
	return (pos_in_step);
}

t_point	update_pos_in_pix(t_player *player)
{
	t_point	pos_in_pix;
	t_point	box_pos_in_pix;

	box_pos_in_pix = pix_pos_in_box(player->pos_box);
	pos_in_pix.x = player->pos_map.x * (int)UNITS_PER_BOX + box_pos_in_pix.x;
	pos_in_pix.y = player->pos_map.y * (int)UNITS_PER_BOX + box_pos_in_pix.y;
	if (pos_in_pix.x < 0 || pos_in_pix.y < 0)
		error_msg("[update_pos_in_step] pos_in_step probably overflow");
	player->pos_in_pix = pos_in_pix;
	return (pos_in_pix);
}

