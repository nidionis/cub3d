/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_crossing_box.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:17:56 by suplayerko        #+#    #+#             */
/*   Updated: 2022/12/15 03:45:29 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* algo explained in move_player file */
/* functions returns 1 if a wall is hit */
int	north_crossing(t_data *data)
{
	char	**map;
	t_point	pos_map;

	map = data->map;
	pos_map = data->player->pos_map;
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

	map = data->map;
	pos_map = data->player->pos_map;
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

	map = data->map;
	pos_map = data->player->pos_map;
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

	map = data->map;
	pos_map = data->player->pos_map;
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
