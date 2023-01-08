/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_event.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 11:49:36 by dpaulino          #+#    #+#             */
/*   Updated: 2023/01/04 17:36:27 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub3d_bonus.h"

int	render_game(t_data *data)
{
	world_render(data);
	game_event(data);
	player_smoth_move(data);
	draw_mini_map(data);
	draw_stamina_hud(data);
	if (data->menu->minimap == 1 && data->minimap.state == 1)
		minimap_render(data);
	draw_image(data->img->img, data->menu->background[LAYOUT], \
	y_x(0, 0), 1354);
	mlx_put_image_to_window(data->window->mlx, data->window->init, \
		data->img->img, 0, 0);
	draw_interface(data);
	return (0);
}

void	draw_string(t_data *data)
{
	char	*score;

	score = ft_itoa(data->score);
	if (data->door.state == 1)
	{
		mlx_string_put(data->window->mlx, data->window->init, \
			data->window->width / 2, data->window->height / 2, \
				rgb_conv(255, 255, 255), "GG");
		mlx_string_put(data->window->mlx, data->window->init, \
			data->window->width / 2, data->window->height / 2 + 25, \
			rgb_conv(255, 255, 255), "SCORE");
		mlx_string_put(data->window->mlx, data->window->init, \
			data->window->width / 2, data->window->height / 2 + 50, \
				rgb_conv(255, 255, 255), score);
	}
	else if (data->menu->menu_state == 1)
		mlx_string_put(data->window->mlx, data->window->init, \
			data->window->width / 2, data->window->height / 2, \
				rgb_conv(255, 255, 255), "Quiting...");
	else
		mlx_string_put(data->window->mlx, data->window->init, \
			data->window->width / 2, data->window->height / 2, \
				rgb_conv(255, 255, 255), "GameOver");
	free(score);
}

int	render_game2(t_data *data)
{
	static int	count_to_end;
	int count;
	int test;

	count = 2;
	test = 0;
	if (count_to_end == 500)
		exit_game(data);
	if (data->time_state == 2 && time(NULL) - data->timer > 15)
	{
		while (generate_map(data, count) && (!check_path_door(data, \
			data->player->pos_map.y, data->player->pos_map.x) \
		|| !check_path_switch(data, data->player->pos_map.y, \
			data->player->pos_map.x) || !check_path_map(data, \
			data->player->pos_map.y, data->player->pos_map.x)))
			{
				test++;
				if (test >= 1000)
				{
					ft_free_split(&data->map);
					data->map = copy_map(data, data->cpy_map);
					if (count > 1000)
						break;
					count++; 
					test = 0;
				}
			}
		data->timer = time(NULL);
	}
	else if (data->menu->game_state == 2)
	{
		count_to_end++;
		change_to_black(data, data->img);
		mlx_put_image_to_window(data->window->mlx, data->window->init, \
			data->img->img, 0, 0);
		draw_string(data);
	}
	return (0);
}

int	game_event(t_data *data)
{
	static int	counter;

	counter++;
	mouse_rotate(data);
	if (data->player->speed == 1 && data->player->stamina > 0)
		data->player->stamina--;
	else if (data->player->speed == 0 && data->player->stamina < 100)
		data->player->stamina++;
	if (data->player->stamina < 5)
		data->player->speed = 0;
	if (data->rain_state == 0)
		draw_rain(data, rand() % 20);
	if (data->time_state == 2 && time(NULL) - data->timer > 7)
	{
		if (counter > 100)
			counter = 0;
		if (counter >= 50)
			change(data, data->img);
	}
	return (0);
}
