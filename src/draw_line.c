/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 15:06:18 by dpaulino          #+#    #+#             */
/*   Updated: 2022/11/20 15:21:31 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_line(t_data *data, t_point	*start, t_point	*end, int color)
{
	int	x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
	
    dx = end->x - start->x;
    dy = end->y - start->y;
    dx1 = abs(dx);
    dy1 = abs(dy);
    px = 2 * dy1 - dx1;
    py = 2 * dx1 - dy1;
    if (dy1 <= dx1) {
        if (dx >= 0)
		{
            x = start->x; y = start->y; xe = end->x;
        }
		else
		{
            x = end->x; y = end->y; xe = start->x;
        }
		mlx_pixel_put(data->window->mlx, data->window->init, x, y, color);
        for (i = 0; x < xe; i++)
		{
        	x = x + 1;
        	if (px < 0)
			{
        	    px = px + 2 * dy1;
        	}
			else
			{
        	    if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) {
        	        y = y + 1;
        	    } else {
        	        y = y - 1;
        	    }
        	    px = px + 2 * (dy1 - dx1);
        	}
        	mlx_pixel_put(data->window->mlx, data->window->init, x, y, color);
        }
	}
		else
		{
        	if (dy >= 0)
			{
        	    x = start->x; y = start->y; ye =end-> y;
        	}
			else
			{
        	    x = end->x; y = end->y; ye = start->y;
        	}
			mlx_pixel_put(data->window->mlx, data->window->init, x, y, color);
        	for (i = 0; y < ye; i++)
			{
        	    y = y + 1;
        	    if (py <= 0) {
        	        py = py + 2 * dx1;
        	    } else {
        	        if ((dx < 0 && dy<0) || (dx > 0 && dy > 0)) {
        	            x = x + 1;
        	        } else {
        	            x = x - 1;
        	        }
        	        py = py + 2 * (dx1 - dy1);
        	    }
        	    mlx_pixel_put(data->window->mlx, data->window->init, x, y, color);
        	}
    }
}