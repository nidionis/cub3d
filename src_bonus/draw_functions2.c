/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_functions2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 03:51:59 by dpaulino          #+#    #+#             */
/*   Updated: 2023/01/02 12:54:15 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub3d_bonus.h"

t_point init_stamina_coord(t_data *data)
{
	t_point pos;

	if (data->window->width == 1900)
	{
		pos.y = data->window->height - 100;
		pos.x = 40;
	}
	else if (data->window->width == 1200)
	{
		pos.y = data->window->height - 40;
		pos.x = 40;
	}
	else if (data->window->width == 700)
	{
		pos.y = data->window->height - 40;
		pos.x = 40;
	}
	return (pos);
}
//draw squares making look like a stamina bar
void	draw_stamina_hud(t_data *data)
{
	t_point pos;
	int				red;
	unsigned int	tmp_x;

	red = rgb_conv(200, 0, 0);
	tmp_x = 0;
	pos = init_stamina_coord(data);
	while (tmp_x < data->player->stamina * 2)
	{
		if (data->player->stamina > 30)
		{
			draw_cube(data, 5, y_x(pos.y, pos.x + (tmp_x)), rgb_conv(200, 200, 200));
			draw_cube(data, 5, y_x(pos.y + 4, pos.x + (tmp_x)), rgb_conv(200, 200, 200));
			draw_cube(data, 5, y_x(pos.y + 8, pos.x + (tmp_x)), rgb_conv(200, 200, 200));
		}
		else
		{
			draw_cube(data, 5, y_x(pos.y, pos.x + (tmp_x)), red);
			draw_cube(data, 5, y_x(pos.y + 4, pos.x + (tmp_x)), red);
			draw_cube(data, 5, y_x(pos.y + 8, pos.x + (tmp_x)), red);
		}
		tmp_x += 4;
	}
}

//create random lines to make look like rain
void	draw_rain(t_data *data, int lines)
{
	t_point	start;
	t_point	end;
	int		i;

	i = 0;
	while (i < lines)
	{
		start.x = rand() % data->window->width - 1;
		start.y = 0;
		end.x = start.x + (rand() - RAND_MAX / 2) % 50;
		end.y = data->window->height - 1;
		draw_line(data, &start, &end, rgb_conv(255, 255, 255));
		i++;
	}
}
