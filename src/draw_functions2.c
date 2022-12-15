/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_functions2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 03:51:59 by dpaulino          #+#    #+#             */
/*   Updated: 2022/12/14 04:18:16 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

//draw squares making look like a stamina bar
void	draw_stamina_hud(t_data *data)
{
	int				x;
	int				y;
	int				red;
	unsigned int	tmp_x;

	red = rgb_conv(200, 0, 0);
	tmp_x = 0;
	x = 40;
	y = 980;
	while (tmp_x < data->player->stamina * 3)
	{
		if (data->player->stamina > 30)
		{
			draw_cube(data, 5, y, x + (tmp_x), rgb_conv(200, 200, 200));
			draw_cube(data, 5, y + 4, x + (tmp_x), rgb_conv(200, 200, 200));
			draw_cube(data, 5, y + 8, x + (tmp_x), rgb_conv(200, 200, 200));
		}
		else
		{
			draw_cube(data, 5, y, x + (tmp_x), red);
			draw_cube(data, 5, y + 4, x + (tmp_x), red);
			draw_cube(data, 5, y + 8, x + (tmp_x), red);
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
		start.x = rand() % SCREEN_WIDTH - 1;
		start.y = 0;
		end.x = start.x + (rand() - RAND_MAX / 2) % 50;
		end.y = SCREEN_HEIGHT - 1;
		draw_line(data, &start, &end, rgb_conv(255, 255, 255));
		i++;
	}
}
