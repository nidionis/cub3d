/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gg_window_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 20:45:24 by dpaulino          #+#    #+#             */
/*   Updated: 2022/10/31 11:00:18 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_cube(t_window *window, int size, int pos_x, int pos_y)
{
	int	y;
	int	x;

	x = pos_x - (size / 2);
	y = pos_y - (size / 2);
	while (y < pos_y + (size / 2))
	{
		while (x < pos_x + (size / 2))
		{
			mlx_pixel_put(window->mlx, window->init, x, y, 0xFFFFFF);
			x++;
		}
		x = pos_x - (size / 2);
		y++;
	}
}

void	render_map_2d(t_data *data)
{
	t_window	*window;

	window = data->window;
	draw_cube(window, 30, 200, 200);
	mlx_loop(data->window->mlx);
}

int	window_init(t_window *window)
{
	window->mlx = mlx_init();
	window->init = mlx_new_window(window->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "test");
	return (0);
}
