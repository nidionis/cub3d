/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 20:45:24 by dpaulino          #+#    #+#             */
/*   Updated: 2022/11/23 09:55:27 by dpaulino         ###   ########.fr       */
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

void	load_textures(t_data *data)
{
	t_window *window;

	int width;
	int height;

	width = 20;
	height = 20;
	window = data->window;
	data->textures = malloc(sizeof(t_img_data));
	data->textures->img = mlx_xpm_file_to_image(window->mlx, \
	"assets/wall.xpm", &width, &height);
	data->textures->adress = mlx_get_data_addr(data->textures->img, \
	&data->textures->bpp, &data->textures->line_len, &data->textures->endian);
}

/* draw_ray */
int	window_init(t_data *data)
{
	t_window *window;

	window = data->window;
	window->mlx = mlx_init();
	data->img = malloc(sizeof(t_img_data));
	load_textures(data);
	data->img->img = mlx_new_image(window->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	window->init = mlx_new_window(window->mlx, \
		SCREEN_WIDTH, SCREEN_HEIGHT, "test");
	data->img->adress = mlx_get_data_addr(data->img->img,&data->img->bpp, &data->img->line_len, &data->img->endian);
	mlx_put_image_to_window(window->mlx, window->init, data->img->img,0, 0);
	return (0);
}
