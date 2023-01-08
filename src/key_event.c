/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 14:57:02 by dpaulino          #+#    #+#             */
/*   Updated: 2023/01/04 18:50:26 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	fix_ang(int a)
{
	if (a > 359)
	{
		a -= 360;
	}
	if (a < 0)
	{
		a += 360;
	}
	return (a);
}

void	init_key_status(t_data *data)
{
	data->key_status = malloc(sizeof(t_key_status));
	data->key_status->a = 0;
	data->key_status->d = 0;
	data->key_status->w = 0;
	data->key_status->s = 0;
	data->key_status->left = 0;
	data->key_status->right = 0;
	data->key_status->sprint = 0;
	data->key_status->config = 0;
	data->game_state = 1;
}

void	control_key_press(int key, t_data *data)
{
	if (key == ENTER)
	{
		if (data->menu->back == 1)
		{
			data->menu->back = 0;
			data->menu->controls_state = 0;
			data->menu->menu_state = 1;
			data->menu->controls = 1;
			clear_img(data->menu->background[BG]);
		}
	}
}

int	key_press(int key, t_data *data)
{
	key_game(key, data);
	if (key == KEY_ESC)
	{
		if (data->game_state == 1)
			data->game_state = 2;
		else
			exit_game(data);
	}
	return (0);
}

int	key_realese(int key, t_data *data)
{
	if (key == KEY_W)
		data->key_status->w = 0;
	else if (key == KEY_S)
		data->key_status->s = 0;
	else if (key == KEY_A)
		data->key_status->a = 0;
	else if (key == KEY_D)
		data->key_status->d = 0;
	else if (key == KEY_RIGHT)
		data->key_status->right = 0;
	else if (key == KEY_LEFT)
		data->key_status->left = 0;
	return (0);
}
