/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:14:23 by dpaulino          #+#    #+#             */
/*   Updated: 2022/12/15 17:24:56 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
			random = rand() % 2;
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

void	init_new_old_map(t_point *new, t_point *old)
{
	new->x = 0;
	new->y = 0;
	old->x = 0;
	old->y = 0;
}

void	draw_map_border(t_data *data, int size_y, int size_x)
{
	char	**new_map;
	t_point	old;
	t_point	new;

	init_new_old_map(&new, &old);
	new_map = alloc_mem(size_y + 2, size_x + 2);
	while (new.y < size_y + 2)
	{
		while (new.x < size_x + 2)
		{
			if (new.x == 0 || new.y == 0 || new.x == size_x + 1 \
			|| new.y == size_y + 1)
				new_map[new.y][new.x++] = '1';
			else
			{
				if (data->map[old.y][old.x] == ' ')
					new_map[new.y][new.x++] = '1';
				else
					new_map[new.y][new.x++] = data->map[old.y][old.x++];
			}
		}
		new_map[new.y][new.x] = '\0';
		if (new.y++ != 0 && new.y != size_y + 1)
			old.y++;
		new.x = 0;
		old.x = 0;
	}
	new_map[new.y - 1] = NULL;
	ft_free_split(&data->map);
	data->map = new_map;
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

void	generate_map_content(t_data *data, t_assets *asset, char c)
{
	t_point	pos;
	int		wall_side;

	if (asset->done == 1)
		data->map[asset->pos.y][asset->pos.x] = '1';
	check_content_side(data, &wall_side, asset, &pos);
	if (wall_side == 4)
	{
		pos.x = data->map_width - 2;
		pos.y = rand() % data->map_height - 2;
		if (pos.y <= 0)
			pos.y = 1;
		asset->side = EAST;
	}
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
