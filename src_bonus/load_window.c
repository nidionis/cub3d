/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 20:45:24 by dpaulino          #+#    #+#             */
/*   Updated: 2023/01/02 12:56:18 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub3d_bonus.h"

t_point	units_pos_to_minimap_pos(t_data *data, t_point absolute_position)
{
	t_point		pos_for_map;
	double		u;
	double		wall_size;

	(void)data;
	u = (double)UNITS_PER_BOX;
	wall_size = (double)WALL_SIZE;
	pos_for_map.x = wall_size * ((((double)absolute_position.x) / u));
	pos_for_map.y = wall_size * ((((double)absolute_position.y) / u));
	return (pos_for_map);
}

int	load_window(t_data *data)
{
	t_window	*window;

	window = data->window;
	data->img = malloc(sizeof(t_img_data));
	if (g_status == 0)
	{
		window->height = SCREEN_HEIGHT;
		window->width = SCREEN_WIDTH;
	}
	else if (g_status == 1)
	{
		window->width = 1900;
		window->height = 1080;
	}
	else if (g_status == 2)
	{
		window->width = 1200;
		window->height = 700;
	}
	else if (g_status == 3)
	{
		window->width = 700;
		window->height = 500;
	}
	data->img->img = mlx_new_image(window->mlx, window->width, window->height);
	window->init = mlx_new_window(window->mlx, \
		window->width, window->height, "Cub3d");
	data->img->line_len = data->img->line_len >> 2;
	data->img->address = (int *)mlx_get_data_addr(data->img->img, \
		&data->img->bpp, &data->img->line_len, &data->img->endian);
	load_menu(data);
	return (0);
}
