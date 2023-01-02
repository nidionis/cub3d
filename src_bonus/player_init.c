/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 14:49:59 by dpaulino          #+#    #+#             */
/*   Updated: 2023/01/02 12:57:19 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub3d_bonus.h"


//Function used to update player after adding the board on map
void	update_player(char **map, t_player *player)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (map[y])
	{
		while (map[y][x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'W' || \
			map[y][x] == 'E' || map[y][x] == 'S')
			{
				player->pos_map.x = x;
				player->pos_map.y = y;
				player->pos_box.x = UNITS_PER_BOX / 2;
				player->pos_box.y = UNITS_PER_BOX / 2;
				player->pos_in_step = update_pos_in_step(player);
				player->pos_in_pix = update_pos_in_pix(player);
				return ;
			}
			x++;
		}
		x = 0;
		y++;
	}
}
