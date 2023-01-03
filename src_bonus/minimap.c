/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 09:30:16 by dpaulino          #+#    #+#             */
/*   Updated: 2023/01/03 10:03:27 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub3d_bonus.h"

void	put_cube_minimap(t_data *data, t_point pos, t_point pos2)
{
	if (data->map[pos.y] && data->map[pos.y][pos.x] && \
			data->map[pos.y][pos.x] == '1')
		draw_cube(data, WALL_SIZE, y_x(pos2.y * WALL_SIZE + \
			(WALL_SIZE / 2), pos2.x * WALL_SIZE + (WALL_SIZE / 2)), \
			rgb_conv(255, 255, 255));
	else if (pos.x == data->player->pos_map.x && pos.y == \
		data->player->pos_map.y)
		draw_cube(data, WALL_SIZE, y_x(pos2.y * WALL_SIZE + \
			(WALL_SIZE / 2), pos2.x * WALL_SIZE + (WALL_SIZE / 2)), \
			rgb_conv(0, 0, 0));
	else
		draw_cube(data, WALL_SIZE, y_x(pos2.y * WALL_SIZE + \
			(WALL_SIZE / 2), pos2.x * WALL_SIZE + (WALL_SIZE / 2)), \
			rgb_conv(180, 180, 180));
}

t_point	init_pos(t_data *data)
{
	t_point	pos;

	pos.x = data->player->pos_map.x - 5;
	pos.y = data->player->pos_map.y - 5;
	return (pos);
}

t_point	init_pos2(void)
{
	t_point	pos2;

	pos2.x = 0;
	pos2.y = 0;
	return (pos2);
}

void	draw_mini_map(t_data *data)
{
	t_point	pos;
	t_point	pos2;

	pos = init_pos(data);
	pos2 = init_pos2();
	if (pos.x < 0)
		pos.x = 0;
	if (pos.y < 0)
		pos.y = 0;
	while (data->map[pos.y] && pos.y < data->player->pos_map.y + 5)
	{
		while (data->map[pos.y][pos.x] && pos.x < data->player->pos_map.x + 5)
		{
			put_cube_minimap(data, pos, pos2);
			pos2.x++;
			pos.x++;
		}
		pos2.y++;
		pos2.x = 0;
		pos.x = data->player->pos_map.x - 5;
		if (pos.x < 0)
		pos.x = 0;
		pos.y++;
	}
}
