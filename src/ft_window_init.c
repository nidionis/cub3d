/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_window_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 20:45:24 by dpaulino          #+#    #+#             */
/*   Updated: 2022/11/11 13:01:05 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*
Algo :
	scale wall to map size (and keep walls as square)
	whe should use "pos_in_step (or pos_in_pix) to get the absolute value of the player
	[if I didn't mess my functions] the side len of a wall considering pos_in_step is equal to STEP_PER_BOX
	example:
	STEP_PER_BOX = 3,
	player.pos_in_step.x = 4
	player.pos_in_step.y = 3
	 ___ ___
	|   |   |
	|   |   |
	|___|___|
	|   | p |
	|   |   |
	|___|___|
We could use UNIT_PER_BOX scale too
(I reckon UNIT_PER_BOX for pix points)
if UNITS_PER_BOX = 1000,
	player.pos_in_pix.x = 1000 + 1000 / 3 = 1333
	player.pos_in_pix.y = 1000 + 0 / 3    = 1000

	general rule:
	pos_box_in_pix = (pos_box / STEP_PER_BOX) * UNIT_PER_BOX
	pos_in_pix = (pos_map * UNITS_PER_BOX) + pos_box_in_pix

functions are in pos_update.c
*/
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

t_point	units_pos_to_minimap_pos(t_data *data, t_point absolute_position)
{
	t_point		pos_for_map;
	double		u;
	double		wall_size;
	(void)data;
	
	u = (double)UNITS_PER_BOX;
	wall_size = (double)WALL_SIZE + 1;
	pos_for_map.x = wall_size * ((((double)absolute_position.x) / u));
	pos_for_map.y = wall_size * ((((double)absolute_position.y) / u));
	return (pos_for_map);
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
			end = units_pos_to_minimap_pos(data, data->cam->arRay[i].hit_point);//dx
			draw_line(data, &minimap_position, &end, rgb_conv(100, 100, 100));
		i++;
	}
		end.x = minimap_position.x + data->player->direction.x * 15;//dx
		end.y = minimap_position.y + data->player->direction.y * 15;// dy
		draw_line(data, &minimap_position, &end, rgb_conv(100, 100, 100));
}

void	draw_player(t_data *data)
{
	t_player *player;
	t_point		minimap_position;

	player = data->player;
	minimap_position = units_pos_to_minimap_pos(data, player->pos_in_pix);
	draw_cube(data->window, 5, minimap_position.y, minimap_position.x, 0x0F0F0F);
    draw_vision_field(data, minimap_position);
}

void	draw_mini_map(t_data *data)
{
	t_point	pos;
	int i;
	int j;

	j = 0;
	i = 0;
	pos.x = 0;
	pos.y = 0;
	while (data->map[pos.y])	{
		while (data->map[pos.y][pos.x])
		{
			if (data->map[pos.y][pos.x] == '1')
				draw_cube(data->window, WALL_SIZE, pos.y * WALL_SIZE + \
					(WALL_SIZE / 2) + j, pos.x * WALL_SIZE + (WALL_SIZE / 2) + i, 0xF00F0F);
			i++;
			pos.x++;
		}
		j++;
		i = 0;
		pos.x = 0;
		pos.y++;
	}
	//draw_player(data);
}

/* draw_ray */
int	ray_cast(t_data *data)
{
	int	i;

	i = 0;
	set_arRay(data);
	while (i < CAM_QUALITY)
	{
		draw_wall_line(data, i);
		i++;
	}
	render_map_2d(data);
	return (0);
}

int	render_map_2d(t_data *data)
{
	(void)data;
	draw_mini_map(data);
	draw_player(data);
	// mlx_clear_window(data->window->mlx, data->window->init);
	return (0);
}

int	window_init(t_window *window)
{
	window->mlx = mlx_init();
	window->init = mlx_new_window(window->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "test");
	return (0);
}
