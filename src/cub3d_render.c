/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 15:08:38 by dpaulino          #+#    #+#             */
/*   Updated: 2022/12/13 15:22:56 by dpaulino         ###   ########.fr       */
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
		"assets/textures/wall20x20.xpm", &a, &b);
	data->image->texture_path[1] = mlx_xpm_file_to_image(data->window->mlx, \
		"assets/textures/floors.xpm", &a, &b);
	draw_mini_map(data);
	return (0);
}

void draw_rain(t_data *data, int lines)
{
	t_point start;
	t_point end;
	int i;

	i = 0;
	while (i < lines)
	{
		start.x = rand() % SCREEN_WIDTH - 1;
   		start.y = 0;
		end.x = start.x + (rand() - RAND_MAX / 2) % 50;
    	end.y = SCREEN_HEIGHT - 1;
		draw_line(data, &start, &end, rgb_conv(255,255,255));
		i++;
	}
}

//generate the 3d world with raycast
void	world_render(t_data *data)
{
	int	i;

	i = 0;
	set_arRay(data);
	draw_ceiling_floor_mandatory(data);
	while (i < CAM_QUALITY)
	{	
		draw_wall_textured(data, i);
		i++;
	}
}
void	draw_stamina_hud(t_data *data)
{
	int x;
	int y;
	int red;

	red = rgb_conv(200, 0, 0);
	unsigned int a;
	a = 0;
	
	x = 40;
	y = 980;
	while (a < data->player->stamina * 3)
	{
		if (data->player->stamina > 30)
		{
			draw_cube(data, 5, y, x + (a),rgb_conv(200,200,200));
			draw_cube(data, 5, y + 4, x + (a),rgb_conv(200,200,200));
			draw_cube(data, 5, y + 8, x + (a),rgb_conv(200,200,200));
		}
		else
		{
			draw_cube(data, 5, y, x + (a),red);
			draw_cube(data, 5, y + 4, x + (a),red);
			draw_cube(data, 5, y + 8, x + (a),red);
		}
		
		a+=4;
	}

}
void		mouse_rotate(t_data *data)
{
	t_point		pos;
	t_point		delta;

	if (data->mouse == 0)
		return ;
	// mlx_mouse_get_pos(data->window->mlx, data->window->init, &pos.x, &pos.y);linux
	mlx_mouse_get_pos(data->window->init, &pos.x, &pos.y);
	delta.x = pos.x - SCREEN_WIDTH/2;
	delta.y = pos.y - SCREEN_HEIGHT/2;
	if (delta.x < 0)
		rotate_player(data->player,LEFT);
	else if (delta.x > 0)
		rotate_player(data->player,RIGHT);
	// mlx_mouse_move(data->window->mlx, data->window->init, SCREEN_WIDTH/2, SCREEN_HEIGHT/2); linux
	mlx_mouse_move(data->window->init, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
}
//world_render generate the 3d world with raycast
//player_smoth detects key pressure to make player move
//mini_map_render generate the minimap if key M is pressed
int set_red_to_max(int color) {
    // Extract the red, green, and blue components from the color value
    int r = (color >> 16) & 0xff;
    int g = (color >> 8) & 0xff;
    int b = color & 0xff;

    // Set the red value to 255
    r = 255;

    // Return the resulting color as a single integer value
    return (r << 16) | (g << 8) | b;
}
void change(t_img_data *img)
{
	int i;

	i = 0;
	while(i < 1900 * 1080)
	{
		img->address[i] = set_red_to_max(img->address[i]);
		i++;
	}
}
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
		if (data->mouse == 1)
			mouse_rotate(data);
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
				change(data->img);
			
		}
		draw_image(data->img, data->menu->background[4], y_x(SCREEN_HEIGHT / 2 + 267, SCREEN_WIDTH/2 - (SCREEN_WIDTH/3)), -1);
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
	else
		render_menu(data);
	return (0);
}

int mouse_event(t_data *data)
{
	data->mouse = 1;
	mlx_mouse_hide(data->window->mlx,data->window->init);
	return (0);
}

int	cub3d_render(t_data *data)
{
	mlx_hook(data->window->init, 2, 1L << 0, key_press, data);
	mlx_hook(data->window->init, 3, 1L << 1, key_realese, data);
	mlx_loop_hook(data->window->mlx, graphics_render, data);
	mlx_hook(data->window->init,12, 1L<<15, mouse_event, data);
	mlx_hook(data->window->init, 17, 1L << 17, &exit_game, data);
	mlx_loop(data->window->mlx);
	return (0);
}
