/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 20:45:24 by dpaulino          #+#    #+#             */
/*   Updated: 2022/12/08 18:00:36 by dpaulino         ###   ########.fr       */
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
// void	load_textures(t_data *data)
// {
// 	data->textures[0].img = mlx_xpm_file_to_image(data->window->mlx, "assets/test.xpm",64, 64);
// 	data->textures[0].adress = mlx_get_data_addr(data->textures[0].img, &data->textures[0].bpp, &data->textures[0].line_len,&data->textures[0].endian);
// }

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

int	load_window(t_data *data)
{
	t_window *window;

	window = data->window;
	data->img = malloc(sizeof(t_img_data));
	window->height = SCREEN_HEIGHT;
	window->width = SCREEN_WIDTH;
	data->img->img = mlx_new_image(window->mlx, window->width, window->height);
	window->init = mlx_new_window(window->mlx, \
		window->width, window->height, "Cub3d");
	data->img->line_len = data->img->line_len >> 2;
	data->img->address = (int *)mlx_get_data_addr(data->img->img,&data->img->bpp, &data->img->line_len, &data->img->endian);
	load_menu(data);
	return (0);
}
