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

t_point	get_map_position_from_absolute_UNIT_PER_BOX_position(t_point absolute_pos)
{
	t_point	map_pos;

	map_pos.x = absolute_pos.x / (int)UNITS_PER_BOX;
	map_pos.y = absolute_pos.y / (int)UNITS_PER_BOX;
	return (map_pos);
}

char	get_map_case_from_absolute_UNIT_PER_BOX_position(t_point absolute_pos, char **map)
{
	t_point	map_pos;

	map_pos = get_map_position_from_absolute_UNIT_PER_BOX_position(absolute_pos);
	return (map[map_pos.x][map_pos.y]);
}
