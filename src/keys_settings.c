/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_settings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 12:37:48 by dpaulino          #+#    #+#             */
/*   Updated: 2022/12/05 13:40:35 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	settings_enter_key(t_data *data)
{
	if (data->menu->resolution == 1)
	{
		data->menu->resolution = 0;
		data->menu->high_res = 1;
		data->menu->settings_state = 0;
		data->menu->resolution_state = 1;
		clear_img(data->menu->background[BG]);
	}
	else if (data->menu->back == 1)
	{
		data->menu->settings_state = 0;
		data->menu->back = 0;
		data->menu->menu_state = 1;
		data->menu->settings = 1;
		clear_img(data->menu->background[BG]);
	}
}

void	settings_w_key(t_data *data)
{
	if (data->menu->resolution == 1)
	{
		data->menu->resolution = 0;
		data->menu->back = 1;
	}
	else if (data->menu->back == 1 && data->menu->settings_state == 1)
	{
		data->menu->back = 0;
		data->menu->sensivity = 1;
	}
	else if (data->menu->sensivity == 1)
	{
		data->menu->sensivity = 0;
		data->menu->resolution = 1;
	}
}

void	settings_s_key(t_data *data)
{
	if (data->menu->resolution == 1)
	{
		data->menu->resolution = 0;
		data->menu->sensivity = 1;
	}
	else if (data->menu->back == 1 && data->menu->settings_state == 1)
	{
		data->menu->back = 0;
		data->menu->resolution = 1;
	}
	else if (data->menu->sensivity == 1)
	{
		data->menu->sensivity = 0;
		data->menu->back = 1;
	}
}

void	settings_key_press(int key, t_data *data)
{
	if (key == ENTER)
	{
		settings_enter_key(data);
	}
	if (key == KEY_W)
	{
		settings_w_key(data);
	}
	if (key == KEY_S)
	{
		settings_s_key(data);
	}
}
