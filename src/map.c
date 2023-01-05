/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 10:03:30 by dpaulino          #+#    #+#             */
/*   Updated: 2023/01/04 17:43:44 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	put_cube_map(t_data *data, t_point pos, int wall)
{
	if (data->map[pos.y][pos.x] == '0')
		draw_cube(data, wall, y_x(pos.y * wall + \
			(wall / 2), pos.x * wall + (wall / 2)), rgb_conv(0, 160, 0));
	else if (data->map[pos.y][pos.x] == 'E' || data->map[pos.y][pos.x] \
	== 'W' || data->map[pos.y][pos.x] == 'S' || data->map[pos.y][pos.x] == 'N')
		draw_cube(data, wall, y_x(pos.y * wall + \
			(wall / 2), pos.x * wall + (wall / 2)), rgb_conv(255, 255, 255));
	else
		draw_cube(data, wall, y_x(pos.y * wall + \
			(wall / 2), pos.x * wall + (wall / 2)), rgb_conv(180, 10, 10));
}

void	draw_map(t_data *data)
{
	t_point	pos;
	int		i;
	int		j;
	int		wall;

	wall = WALL_SIZE;
	j = 0;
	i = 1;
	pos.x = 1;
	pos.y = 1;
	while (pos.y < data->map_height - 1)
	{
		while (pos.x < data->map_width - 1)
		{
			put_cube_map(data, pos, wall);
			i++;
			pos.x++;
		}
		j++;
		i = 0;
		pos.x = 1;
		pos.y++;
	}
	draw_player(data);
}
