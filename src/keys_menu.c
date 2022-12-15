/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 12:42:08 by dpaulino          #+#    #+#             */
/*   Updated: 2022/12/15 03:40:55 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	menu_enter_key2(t_data *data)
{
	if (data->menu->settings == 1)
	{
		data->menu->menu_state = 0;
		data->menu->resolution = 1;
		data->menu->settings_state = 1;
		data->menu->settings = 0;
		clear_img(data->menu->background[BG]);
	}
	if (data->menu->quit == 1)
		exit_game(data);
	if (data->menu->controls == 1)
		data->menu->menu_state = 0;
	if (data->menu->extras == 1)
		data->menu->menu_state = 0;
}

void	menu_enter_key(t_data *data)
{
	if (data->menu->controls == 1)
	{
		data->menu->controls = 0;
		data->menu->menu_state = 0;
		data->menu->back = 1;
		data->menu->controls_state = 1;
		clear_img(data->menu->background[BG]);
		draw_image(data->menu->background[BG], data->menu->background[13], \
		y_x(300, 100), rgb_conv(rand() % 155, rand() % 155, rand() % 155));
	}
	if (data->menu->new_game == 1)
	{
		data->menu->game_state = 1;
		data->menu->menu_state = 0;
	}
	menu_enter_key2(data);
}

void	menu_w_key(t_data *data)
{
	if (data->menu->new_game == 1)
	{
		data->menu->quit = 1;
		data->menu->new_game = 0;
	}
	else if (data->menu->settings == 1)
	{
		data->menu->extras = 1;
		data->menu->settings = 0;
	}
	else if (data->menu->extras == 1)
	{
		data->menu->extras = 0;
		data->menu->controls = 1;
	}
	else if (data->menu->controls == 1)
	{
		data->menu->controls = 0;
		data->menu->new_game = 1;
	}
	else if (data->menu->quit == 1)
	{
		data->menu->quit = 0;
		data->menu->settings = 1;
	}
}

void	menu_s_key(t_data *data)
{
	if (data->menu->new_game == 1)
	{
		data->menu->controls = 1;
		data->menu->new_game = 0;
	}
	else if (data->menu->settings == 1)
	{
		data->menu->quit = 1;
		data->menu->settings = 0;
	}
	else if (data->menu->extras == 1)
	{
		data->menu->extras = 0;
		data->menu->settings = 1;
	}
	else if (data->menu->controls == 1)
	{
		data->menu->controls = 0;
		data->menu->extras = 1;
	}
	else if (data->menu->quit == 1)
	{
		data->menu->quit = 0;
		data->menu->new_game = 1;
	}
}

void	menu_key_press(int key, t_data *data)
{
	if (key == ENTER)
	{
		menu_enter_key(data);
	}
	if (key == KEY_W)
	{
		menu_w_key(data);
	}
	if (key == KEY_S)
	{
		menu_s_key(data);
	}
}
