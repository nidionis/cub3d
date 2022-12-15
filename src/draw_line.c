/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 15:06:18 by dpaulino          #+#    #+#             */
/*   Updated: 2022/12/15 17:28:51 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_x_line(t_data *data, t_line *line, int color)
{
	line->x = line->x + 1;
	if (line->px < 0)
	{
		line->px = line->px + 2 * line->dy1;
	}
	else
	{
		if ((line->dx < 0 && line->dy < 0) || (line->dx > 0 && line->dy > 0))
		{
			line->y = line->y + 1;
		}
		else
		{
			line->y = line->y - 1;
		}
		line->px = line->px + 2 * (line->dy1 - line->dx1);
	}
	my_mlx_pixel_put(data->img, line->x, line->y, color);
	line->i++;
}

void	draw_y_line(t_data *data, t_line *line, int color)
{
	line->y = line->y + 1;
	if (line->py <= 0)
	{
		line->py = line->py + 2 * line->dx1;
	}
	else
	{
		if ((line->dx < 0 && line->dy < 0) || (line->dx > 0 && line->dy > 0))
		{
			line->x = line->x + 1;
		}
		else
		{
			line->x = line->x - 1;
		}
		line->py = line->py + 2 * (line->dx1 - line->dy1);
	}
	my_mlx_pixel_put(data->img, line->x, line->y, color);
	line->i++;
}

void	check_dx_value(t_line *line, t_point	*start, t_point	*end)
{
	if (line->dx >= 0)
	{
		line->x = start->x;
		line->y = start->y;
		line->xe = end->x;
	}
	else
	{
		line->x = end->x;
		line->y = end->y;
		line->xe = start->x;
	}
}

void	check_dy_value(t_line *line, t_point	*start, t_point	*end)
{
	if (line->dy >= 0)
	{
		line->x = start->x;
		line->y = start->y;
		line->ye = end->y;
	}
	else
	{
		line->x = end->x;
		line->y = end->y;
		line->ye = start->y;
	}
}

void	draw_line(t_data *data, t_point	*start, t_point	*end, int color)
{
	t_line	line;

	init_line_values(&line, start, end);
	if (line.dy1 <= line.dx1)
	{
		check_dx_value(&line, start, end);
		my_mlx_pixel_put(data->img, line.x, line.y, color);
		line.i = 0;
		while (line.x < line.xe)
			draw_x_line(data, &line, color);
	}
	else
	{
		check_dy_value(&line, start, end);
		my_mlx_pixel_put(data->img, line.x, line.y, color);
		line.i = 0;
		while (line.y < line.ye)
			draw_y_line(data, &line, color);
	}
}
