/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 15:03:28 by dpaulino          #+#    #+#             */
/*   Updated: 2022/11/28 10:46:04 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_cube(t_data *data, int size, int pos_y, int pos_x, int color)
{
	int	y;
	int	x;

	x = pos_x - (size / 2);
	y = pos_y - (size / 2);
	while (y < pos_y + (size / 2))
	{
		while (x < pos_x + (size / 2))
		{
			my_mlx_pixel_put(data->img, x, y, color);
			x++;
		}
		x = pos_x - (size / 2);
		y++;
	}
}

void	draw_player(t_data *data)
{
	t_player	*player;
	t_point		minimap_position;
	
	player = data->player;
	minimap_position = units_pos_to_minimap_pos(data, player->pos_in_pix);
	draw_cube(data, 5, minimap_position.y, minimap_position.x, 0xFF0F0F);
	draw_vision_field(data, minimap_position);
}

void	draw_mini_map(t_data *data)
{
	t_point	pos;
	int		i;
	int		j;

	j = 0;
	i = 0;
	pos.x = 0;
	pos.y = 0;
	while (data->map[pos.y])
	{
		while (data->map[pos.y][pos.x])
		{
			if (data->map[pos.y][pos.x] == '1')
				draw_cube(data, WALL_SIZE, pos.y * WALL_SIZE + \
					(WALL_SIZE / 2) + j, pos.x * WALL_SIZE + (WALL_SIZE / 2) + i, 0xF0F00F);
				// mlx_put_image_to_window(data->window->mlx, data->window->init, 
				// 	data->image->texture_path[0], pos.x * WALL_SIZE + i, 
				// 	pos.y * WALL_SIZE + j);
			else
				draw_cube(data, WALL_SIZE, pos.y * WALL_SIZE + \
					(WALL_SIZE / 2) + j, pos.x * WALL_SIZE + (WALL_SIZE / 2) + i, 0x0FFF0F);
				// mlx_put_image_to_window(data->window->mlx, data->window->init, 
				// 	data->image->texture_path[1], pos.x * WALL_SIZE + i, 
				// 	pos.y * WALL_SIZE + j);
			i++;
			pos.x++;
		}
		j++;
		i = 0;
		pos.x = 0;
		pos.y++;
	}
	draw_player(data);
}

void	draw_vision_field(t_data *data, t_point minimap_position)
{
	t_point		end;
	int			i;
	int			nb_ray;

	i = 0;
	nb_ray = 5;
	(void)nb_ray;
	while (i < CAM_QUALITY)
	{
		end = units_pos_to_minimap_pos(data, data->cam->arRay[i].hit_point);
		draw_line(data, &minimap_position, &end, rgb_conv(100, 100, 100));
		i++;
	}
	end.x = minimap_position.x + data->player->direction.x * 15;
	end.y = minimap_position.y + data->player->direction.y * 15;
	draw_line(data, &minimap_position, &end, rgb_conv(100, 100, 100));
}