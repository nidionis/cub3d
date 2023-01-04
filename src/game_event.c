/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_event.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 11:49:36 by dpaulino          #+#    #+#             */
/*   Updated: 2023/01/04 18:41:26 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	render_game(t_data *data)
{
	world_render(data);
	player_smoth_move(data);
	mlx_put_image_to_window(data->window->mlx, data->window->init, \
		data->img->img, 0, 0);
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

	if (count_to_end == 500)
		exit_game(data);
	if (data->time_state == 2 && time(NULL) - data->timer > 15)
	{
		while (generate_map(data) && (!check_path_door(data, \
			data->player->pos_map.y, data->player->pos_map.x) \
		|| !check_path_switch(data, data->player->pos_map.y, \
			data->player->pos_map.x) || !check_path_map(data, \
			data->player->pos_map.y, data->player->pos_map.x)))
			(void)data;
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
