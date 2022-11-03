/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_player_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 14:49:59 by dpaulino          #+#    #+#             */
/*   Updated: 2022/11/02 17:48:24 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	player_init(char **map, t_player *player)
{
	t_point	pos;

	pos.x = 0;
	pos.y = 0;
	while (map[pos.y])
	{
		while (map[pos.y][pos.x])
		{
			if (map[pos.y][pos.x] == 'N')
			{
				player->angle = 90;
				player->pos_box.x = pos.x * WALL_SIZE + (WALL_SIZE / 2);
				player->pos_box.y = pos.y * WALL_SIZE + (WALL_SIZE / 2);
				player->pos_map.x = pos.x;
				player->pos_map.y = pos.y;
				player->direction.x = cos(player->angle) * 5;
				player->direction.y = sin(player->angle) * 5;
				return (0);
			}
			pos.x++;
		}
		pos.x = 0;
		pos.y++;
	}	
	return (0);
}
