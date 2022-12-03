/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 15:08:38 by dpaulino          #+#    #+#             */
/*   Updated: 2022/12/01 17:17:35 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	render_map_2d(t_data *data)
{
	int	a;
	int	b;

	a = 20;
	b = 20;
	data->image->texture_path[0] = mlx_xpm_file_to_image(data->window->mlx, \
		"assets/wall20x20.xpm", &a, &b);
	data->image->texture_path[1] = mlx_xpm_file_to_image(data->window->mlx, \
		"assets/floor.xpm", &a, &b);
	draw_mini_map(data);
	draw_player(data);
	return (0);
}

/* dirty way to draw ceiling and floor */
void	draw_ceiling_floor_mandatory(t_data *data)
{
	t_point	p;

	p.y = 0;
	while (p.y < SCREEN_HEIGHT / 2)
	{
		p.x = 0;
		while (p.x < SCREEN_WIDTH)
			my_mlx_pixel_put(data->img, p.x++, p.y, data->image->ceiling_color);
		p.y++;
	}
	while (p.y < SCREEN_HEIGHT)
	{
		p.x = 0;
		while (p.x < SCREEN_WIDTH)
			my_mlx_pixel_put(data->img, p.x++, p.y, data->image->floor_color);
		p.y++;
	}
}
void	check_keys_status(t_data *data)
{
	if (data->key_status->w == 1)
		move_player(data, FORWARD);
	if (data->key_status->s == 1)
		move_player(data, BACKWARD);
	if (data->key_status->a == 1)
		move_player(data, LEFT);
	if (data->key_status->d == 1)
		move_player(data, RIGHT);
	if (data->key_status->left == 1)
		rotate_player(data->player, LEFT);
	if (data->key_status->right == 1)
		rotate_player(data->player, RIGHT);
}

int	graphics_render(t_data *data)
{
	(void)data;
	int	i;

	i = 0;
	set_arRay(data);
	draw_ceiling_floor_mandatory(data);
	while (i < CAM_QUALITY)
	{
		draw_wall_textured(data, i);
		i++;
	}
	check_keys_status(data);
	render_map_2d(data);
	mlx_put_image_to_window(data->window->mlx, data->window->init,data->img->img, 0, 0);
	return (0);
}

int	cub3d_render(t_data *data)
{
	mlx_hook(data->window->init, 2, 1L << 0, key_press, data);
	mlx_hook(data->window->init, 3, 1L << 1, key_realese, data);
	mlx_loop_hook(data->window->mlx, graphics_render, data);
	mlx_hook(data->window->init, 17, 1L << 17, &exit_game, data);
	mlx_loop(data->window->mlx);
	return (0);
}
