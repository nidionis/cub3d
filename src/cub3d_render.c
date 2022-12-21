/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 15:08:38 by dpaulino          #+#    #+#             */
/*   Updated: 2022/12/21 15:16:51 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

//load textures for minimap and render it
int	minimap_render(t_data *data)
{
	int	a;
	int	b;

	a = 20;
	b = 20;
	data->image->texture_path[0] = mlx_xpm_file_to_image(data->window->mlx, \
		"assets/textures/wall20x20.xpm", &a, &b);
	data->image->texture_path[1] = mlx_xpm_file_to_image(data->window->mlx, \
		"assets/textures/floors.xpm", &a, &b);
	draw_mini_map(data);
	return (0);
}

//generate the 3d world with raycast
void	world_render(t_data *data)
{
	int	i;

	i = 0;
	set_array(data);
	draw_ceiling_floor_mandatory(data);
	while (i < data->window->width)
	{	
		draw_wall_textured(data, i);
		i++;
	}
}

//set color red to max value
int	graphics_render(t_data *data)
{
	static int counter;

	counter++;
	if (data->menu->game_state == 1)
	{
		if (data->time_state == 0)
			data->time_state = 1;
		else if (data->time_state == 1)
		{
			data->timer = time(NULL);
			data->time_state = 2;
		}
		world_render(data);
		if (data->rain_state == 0)
			draw_rain(data, rand() % 20);
		// if (data->mouse == 1)
		// 	mouse_rotate(data);
		player_smoth_move(data);
		if (data->menu->minimap == 1 && data->minimap.state == 1)
		{
			minimap_render(data);
		}
		if (data->time_state == 2 && time(NULL) - data->timer > 7)
		{
			if (counter > 100)
				counter = 0;
			if (counter >= 50)
				change(data, data->img);
			
		}
		draw_image(data->img, data->menu->background[LAYOUT], y_x(SCREEN_HEIGHT - 125, SCREEN_WIDTH/2 - 200), -1);
		draw_stamina_hud(data);
		mlx_put_image_to_window(data->window->mlx, data->window->init, \
			data->img->img, 0, 0);
		if (data->time_state == 2)
			mlx_string_put(data->window->mlx,data->window->init,data->window->width / 2 - 450,data->window->height - 120,rgb_conv(255,255,255),ft_itoa(time(NULL) - data->timer));
		if (data->time_state == 2 && time(NULL) - data->timer > 15)
		{
			while(generate_map(data) && (!check_path_door(data,data->player->pos_map.y, data->player->pos_map.x) \
			|| !check_path_switch(data,data->player->pos_map.y, data->player->pos_map.x) || !check_path_map(data,data->player->pos_map.y, data->player->pos_map.x)));
			data->timer = time(NULL);
			printf("generating map\n");
		}
	}
	else if (data->menu->menu_state == 1)
		render_menu(data);
	else if (data->menu->game_state == 2)
		exit_game(data);
	return (0);
}

int	cub3d_render(t_data *data)
{
	mlx_hook(data->window->init, 2, 1L << 0, key_press, data);
	mlx_hook(data->window->init, 3, 1L << 1, key_realese, data);
	mlx_loop_hook(data->window->mlx, graphics_render, data);
	// mlx_hook(data->window->init, 12, 1L << 15, mouse_event, data);
	mlx_hook(data->window->init, 17, 1L << 17, &exit_game, data);
	mlx_loop(data->window->mlx);
	return (0);
}
