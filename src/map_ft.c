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

t_point	get_player_absolute_position(t_player *player)
{
	t_point	abs_pos;

	abs_pos.x = player->pos_map.x * (int)STEPS_PER_BOX + player->pos_box.x;
	abs_pos.y = player->pos_map.y * (int)STEPS_PER_BOX + player->pos_box.y;
	return (abs_pos);
}
