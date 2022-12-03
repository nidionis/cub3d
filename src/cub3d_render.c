/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 15:08:38 by dpaulino          #+#    #+#             */
/*   Updated: 2022/12/03 19:04:38 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	minimap_render(t_data *data)
{
	int	a;
	int	b;

	a = 20;
	b = 20;
	data->image->texture_path[0] = mlx_xpm_file_to_image(data->window->mlx, \
		"assets/wall20x20.xpm", &a, &b);
	data->image->texture_path[1] = mlx_xpm_file_to_image(data->window->mlx, \
		"assets/floor.xpm", &a, &b);
	draw_mini_map(data, 15);
	return (0);
}

//generate the 3d world with raycast
void	world_render(t_data *data)
{
	int	i;

	i = 0;
	set_arRay(data);
	while (i < CAM_QUALITY)
	{	
		draw_wall_line(data, i);
		ft_lstclear(&data->cam->arRay[i].obstacles_ls);
		i++;
	}
}

//world_render generate the 3d world with raycast
//player_smoth detects key pressure to make player move
//mini_map_render generate the minimap if key M is pressed
int	graphics_render(t_data *data)
{
	if (data->menu->start == 1 && data->menu->on == 1)
	{
		world_render(data);
		player_smoth_move(data);
		if (data->menu->menu == 1)
			minimap_render(data);
		
		draw_image(data->img, data->menu->background[4], y_x(SCREEN_HEIGHT /2 + 267,SCREEN_WIDTH/2 - (SCREEN_WIDTH/3)), -1);
		mlx_put_image_to_window(data->window->mlx, data->window->init, \
			data->img->img, 0, 0);
	}
	else
		render_menu(data);
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
