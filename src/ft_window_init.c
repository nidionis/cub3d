/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_window_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 20:45:24 by dpaulino          #+#    #+#             */
/*   Updated: 2022/11/03 14:37:33 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_cube(t_window *window, int size, int pos_y, int pos_x, int color)
{
	int	y;
	int	x;

	x = pos_x - (size / 2);
	y = pos_y - (size / 2);
	while (y < pos_y + (size / 2))
	{
		while (x < pos_x + (size / 2))
		{
			mlx_pixel_put(window->mlx, window->init, x, y, color);
			x++;
		}
		x = pos_x - (size / 2);
		y++;
	}
}

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

void	draw_player(t_data *data)
{
	t_player *player;

	player = data->player;
	draw_cube(data->window, 5, player->pos_box.y, player->pos_box.x, 0xF00F0F);

}

void	draw_mini_map(t_data *data)
{
	t_point	*pos;
	int i;
	int j;

	j = 0;
	i = 0;
	pos = malloc(sizeof(t_point));
	pos->x = 0;
	pos->y = 0;
	while (data->map[pos->y])
	{
		while (data->map[pos->y][pos->x])
		{
			if (data->map[pos->y][pos->x] == '1')
				draw_cube(data->window, WALL_SIZE, pos->y * WALL_SIZE + \
					(WALL_SIZE / 2) + j, pos->x * WALL_SIZE + (WALL_SIZE / 2) + i, 0xF00F0F);
			else
				draw_cube(data->window, WALL_SIZE, pos->y * WALL_SIZE + \
					(WALL_SIZE / 2) + j, pos->x * WALL_SIZE + (WALL_SIZE / 2) + i, 0xf0ff00);
			i++;
			pos->x++;
		}
		j++;
		i = 0;
		pos->x = 0;
		pos->y++;
	}
	draw_player(data);
	free(pos);
}



int	ray_cast(t_data *data)
{
	t_point end;
	
	// draw_cube(data->window, 1200,0, 0, 0xf0ff00);
	end.x = data->player->pos_box.x + data->player->direction.x * 20;//dx
	end.y = data->player->pos_box.y + data->player->direction.y * 20;// dy
	draw_player(data);
	draw_line(data, &data->player->pos_box, &end, 0xfffff0);
	mlx_clear_window(data->window->mlx, data->window->init);
	return (0);
}


int	render_map_2d(t_data *data)
{
	ray_cast(data);
	return (0);
}

int	window_init(t_window *window)
{
	window->mlx = mlx_init();
	window->init = mlx_new_window(window->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "test");
	return (0);
}
