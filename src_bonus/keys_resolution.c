/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_resolution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 12:29:21 by dpaulino          #+#    #+#             */
/*   Updated: 2023/01/02 16:07:28 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub3d_bonus.h"

void	res_enter_key(t_data *data)
{
	char	*argv;

	argv = ft_strdup(data->argv);
	if (data->menu->back == 1)
	{
		data->menu->back = 0;
		data->menu->resolution_state = 0;
		data->menu->settings_state = 1;
		data->menu->resolution = 1;
		clear_img(data->menu->background[BG]);
		return ;
	}
	if (data->menu->high_res == 1)
	{
		mlx_destroy_window(data->window->mlx, data->window->init);
		data->window->init = mlx_new_window(data->window->mlx, \
		1900, 1080, "Cub3d");
		g_status = 1;
		data->menu->game_state = -1;
		// free_everything(data);
		re_run_game(data, argv);
	}
	else if (data->menu->mid_res == 1)
	{
		mlx_destroy_window(data->window->mlx, data->window->init);
		data->window->init = mlx_new_window(data->window->mlx, \
		1200, 700, "Cub3d");
		g_status = 2;
		data->menu->game_state = -1;
		// free_everything(data);
		re_run_game(data, argv);
	}
	else if (data->menu->low_res == 1)
	{
		mlx_destroy_window(data->window->mlx, data->window->init);
		data->window->init = mlx_new_window(data->window->mlx, \
		700, 500, "Cub3d");
		g_status = 3;
		data->menu->game_state = -1;
		// free_everything(data);
		re_run_game(data, argv);
	}
}

void	res_w_key(t_data *data)
{
	if (data->menu->high_res == 1)
	{
		data->menu->high_res = 0;
		data->menu->back = 1;
	}
	if (data->menu->mid_res == 1)
	{
		data->menu->mid_res = 0;
		data->menu->high_res = 1;
	}
	if (data->menu->low_res == 1)
	{
		data->menu->low_res = 0;
		data->menu->mid_res = 1;
	}
	if (data->menu->back == 1)
	{
		data->menu->back = 0;
		data->menu->low_res = 1;
	}
}

void	res_s_key(t_data *data)
{
	if (data->menu->high_res == 1)
	{
		data->menu->high_res = 0;
		data->menu->mid_res = 1;
	}
	else if (data->menu->mid_res == 1)
	{
		data->menu->mid_res = 0;
		data->menu->low_res = 1;
	}
	else if (data->menu->low_res == 1)
	{
		data->menu->low_res = 0;
		data->menu->back = 1;
	}
	else if (data->menu->back == 1)
	{
		data->menu->back = 0;
		data->menu->high_res = 1;
	}
}

void	resolution_key_press(int key, t_data *data)
{
	if (key == ENTER)
	{
		res_enter_key(data);
	}
	if (key == KEY_W)
	{
		res_w_key(data);
	}
	if (key == KEY_S)
	{
		res_s_key(data);
	}
}
