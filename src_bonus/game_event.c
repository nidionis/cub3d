/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_event.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 11:49:36 by dpaulino          #+#    #+#             */
/*   Updated: 2023/01/05 17:04:51 by supersko         ###   ########.fr       */
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

static int map_ok(t_data *data)
{
	if (!check_path_door(data, data->player->pos_map.y, data->player->pos_map.x) \
		|| !check_path_switch(data, data->player->pos_map.y, data->player->pos_map.x)\
		|| !check_path_map(data, data->player->pos_map.y, data->player->pos_map.x))
		return (0);
	return (1);
}

char **dup_map(char **map_i)
{
	char	**new_matrix;

	new_matrix = NULL;
	while (*map_i && **map_i)
	{
		new_matrix = ft_append_tab(new_matrix, ft_strdup(*map_i));
		map_i++;
	}
	return (new_matrix);
}

void	make_new_map(t_data *data)
{
	char	**previous_map;
	char	**tmp;

	tmp = data->map;
	data->map = dup_map(data->map_original);
	ft_free_split(&tmp);
	previous_map = NULL;
	if (!data->map)
		exit_game(data);
	while (generate_map(data) && map_ok(data))
	{
		ft_free_split(&previous_map);
		previous_map = data->map;
		data->map = dup_map(data->map);
	}
	ft_free_split(&data->map);
	data->map = previous_map;
}

int	render_game2(t_data *data)
{
	if (data->time_state == 2 && time(NULL) - data->timer > 15)
	{
		make_new_map(data);
		data->timer = time(NULL);
	}
	else if (data->menu->game_state == 2)
	{
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
