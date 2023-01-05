/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:14:23 by dpaulino          #+#    #+#             */
/*   Updated: 2023/01/05 17:06:15 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub3d_bonus.h"

/*
static int	rand_index(t_data *data)
{
	int		index;
	double	dist;

	dist = sqrt(pow(data->player->pos_map.x - data->door.pos.x, 2) + pow(data->player->pos_map.y - data->door.pos.y, 2));
	fprintf(stderr, "[rand_index]: %d\n", dist);
	index = (int)dist + 2;
	return (index);
}
*/

int	generate_map(t_data *data)
{
	int	y;
	int	x;
	int	random;

	x = 2;
	y = 2;
	while (data->map[y] && y != data->map_height - 2)
	{
		while (data->map[y][x] && x != data->map_width - 2)
		{
			random = rand() % (data->map_width * data->map_height / 200);
			if (data->map[y][x] != 'E' && data->map[y][x] != '2')
			{
				if (random == 1)
					data->map[y][x] = '1';
				else if (random == 0)
					data->map[y][x] = '0';
			}
			x++;
		}
		x = 2;
		y++;
	}
	return (1);
}

void	check_content_side(t_data *data, int *wall_side, t_assets \
*asset, t_point *pos)
{
	*(wall_side) = rand() % 4;
	if (*(wall_side) == 0)
	{
		pos->x = rand() % data->map_width - 2;
		if (pos->x <= 0)
			pos->x = 1;
		pos->y = 1;
		asset->side = NORTH;
	}
	if (*(wall_side) == 1)
	{
		pos->x = rand() % data->map_width - 2;
		if (pos->x <= 0)
			pos->x = 1;
		pos->y = data->map_height - 2;
		asset->side = SOUTH;
	}
	if (*(wall_side) == 3)
	{
		pos->x = 1;
		pos->y = rand() % data->map_height - 2;
		if (pos->y <= 0)
			pos->y = 1;
		asset->side = WEST;
	}
}

void	check_wall_side(t_data *data, int *wall_side, t_point *pos, \
t_assets *asset)
{
	if ((*wall_side) == 4)
	{
		pos->x = data->map_width - 2;
		pos->y = rand() % data->map_height - 2;
		if (pos->y <= 0)
			pos->y = 1;
		asset->side = EAST;
	}
}

void	generate_map_content(t_data *data, t_assets *asset, char c)
{
	t_point	pos;
	int		wall_side;

	pos.x = 0;
	pos.y = 0;
	if (asset->done == 1)
		data->map[asset->pos.y][asset->pos.x] = '1';
	check_content_side(data, &wall_side, asset, &pos);
	check_wall_side(data, &wall_side, &pos, asset);
	if (pos.y < data->map_height && pos.x < data->map_width)
	{
		if (data->map[pos.y][pos.x] != '2' && data->map[pos.y][pos.x] \
		!= '3' && data->map[pos.y][pos.x] != '5')
		{
			data->map[pos.y][pos.x] = c;
			asset->pos.x = pos.x;
			asset->pos.y = pos.y;
			asset->done = 1;
		}
	}
}
