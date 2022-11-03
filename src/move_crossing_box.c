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

/* algo explained in move_player file */
/* functions returns 1 if a wall is hit */

int	north_crossing(t_data *data)
{
	char	**map;
	t_point	pos_map;
	t_point	pos_box;

	map = data->map;
	pos_map = data->player->pos_map;
	pos_box = data->player->pos_box;
	if (is_block(data, map[pos_map.y - 1][pos_map.x]) != -1)
	{
		data->player->pos_box.y = 0;
		return (1);
	}
	else
	{
		data->player->pos_box.y += (int)UNITS_PER_BOX - 1;
		data->player->pos_map.y--;
		return (0);
	}
}

int	south_crossing(t_data *data)
{
	char	**map;
	t_point	pos_map;
	t_point	pos_box;

	map = data->map;
	pos_map = data->player->pos_map;
	pos_box = data->player->pos_box;
	if (is_block(data, map[pos_map.y + 1][pos_map.x]) != -1)
	{
		data->player->pos_box.y = (int)UNITS_PER_BOX - 1;
		return (1);
	}
	else
	{
		data->player->pos_box.y -= (int)UNITS_PER_BOX - 1;
		(data->player->pos_map.y)++;
		return (0);
	}
}

int	east_crossing(t_data *data)
{
	char	**map;
	t_point	pos_map;
	t_point	pos_box;

	map = data->map;
	pos_map = data->player->pos_map;
	pos_box = data->player->pos_box;
	if (is_block(data, map[pos_map.y][pos_map.x - 1]) != -1)
	{
		data->player->pos_box.x = 0;
		return (1);
	}
	else
	{
		data->player->pos_box.x += (int)UNITS_PER_BOX - 1;
		(data->player->pos_map.x)--;
		return (0);
	}
}

int	west_crossing(t_data *data)
{
	char	**map;
	t_point	pos_map;
	t_point	pos_box;

	map = data->map;
	data->player->pos_map;
	data->player->pos_box;
	if (is_block(data, map[pos_map.y][pos_map.x + 1]) != -1)
	{
		data->player->pos_box.x = (int)UNITS_PER_BOX - 1;
		return (1);
	}
	else
	{
		data->player->pos_box.x -= (int)UNITS_PER_BOX - 1;
		(data->player->pos_map.x)++;
		return (0);
	}
}
