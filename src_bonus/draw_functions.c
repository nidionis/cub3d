/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 15:03:28 by dpaulino          #+#    #+#             */
/*   Updated: 2023/01/03 09:30:45 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub3d_bonus.h"

void	draw_player(t_data *data)
{
	t_player	*player;
	t_point		minimap_position;

	player = data->player;
	minimap_position = units_pos_to_minimap_pos(data, player->pos_in_pix);
	draw_cube(data, 5, y_x(minimap_position.y, minimap_position.x), 0xFF0F0F);
	draw_vision_field(data, minimap_position);
}

void	draw_vision_field(t_data *data, t_point minimap_position)
{
	t_point		end;
	int			i;
	int			nb_ray;

	i = 0;
	nb_ray = 5;
	(void)nb_ray;
	while (i < data->window->width)
	{
		end = units_pos_to_minimap_pos(data, data->cam->array[i].hit_point);
		draw_line(data, &minimap_position, &end, rgb_conv(0, 0, 0));
		i++;
	}
	end.x = minimap_position.x + data->player->direction.x * 15;
	end.y = minimap_position.y + data->player->direction.y * 15;
	draw_line(data, &minimap_position, &end, rgb_conv(0, 0, 0));
}

void	draw_ceiling_floor_mandatory(t_data *data)
{
	t_point	p;
	int		height;
	int		width;

	height = get_res_height();
	width = get_res_width();
	p.y = 0;
	while (p.y < height / 2)
	{
		p.x = 0;
		while (p.x < width)
			my_mlx_pixel_put(data->img, p.x++, p.y, data->image->ceiling_color);
		p.y++;
	}
	while (p.y < height)
	{
		p.x = 0;
		while (p.x < width)
			my_mlx_pixel_put(data->img, p.x++, p.y, data->image->floor_color);
		p.y++;
	}
}
