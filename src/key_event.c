/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 14:57:02 by dpaulino          #+#    #+#             */
/*   Updated: 2022/12/04 16:46:15 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int fix_ang(int a)
{
	if(a > 359)
	{
		a -= 360;
	}
	if(a < 0)
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
}

void menu_key_press(int key, t_data *data)
{
	if (key == ENTER)
	{
		if (data->menu->controls == 1)
		{
			data->menu->controls = 0;
			data->menu->menu_state = 0;
			data->menu->back = 1;
			data->menu->controls_state = 1;
			clear_img(data->menu->background[BG]);
			draw_image(data->menu->background[BG],data->menu->background[13], y_x(300, 100),rgb_conv(rand() % 155,rand() % 155,rand() % 155));
		}
		if (data->menu->new_game == 1)
		{
			data->menu->game_state = 1;
		}
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
	if (key == KEY_W)
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
	if (key == KEY_S)
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
}

void settings_key_press(int key, t_data *data)
{
	if (key == ENTER)
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
	if (key == KEY_W)
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
	if (key == KEY_S)
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
}

void control_key_press(int key, t_data *data)
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
void resolution_key_press(int key, t_data *data)
{
	if (key == ENTER)
	{
		if (data->menu->back == 1)
		{
			data->menu->back = 0;
			data->menu->resolution_state = 0;
			data->menu->settings_state = 1;
			data->menu->resolution = 1;
			clear_img(data->menu->background[BG]);
		}
		if (data->menu->mid_res == 1)
		{
			// mlx_destroy_image(data->window->mlx, data->menu->background[BG]);
			// mlx_destroy_image(data->window->mlx, data->img->img);
			mlx_destroy_window(data->window->mlx, data->window->init);
			data->window->init = mlx_new_window(data->window->mlx,1200,700, "hje");
			cub3d_render(data);
		}
	}
	if (key == KEY_W)
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
	if (key == KEY_S)
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
}

int	key_press(int key, t_data *data)
{
	if (data->menu->controls_state == 1)
		control_key_press(key, data);
	else if (data->menu->menu_state == 1)
		menu_key_press(key, data);
	else if (data->menu->settings_state == 1)
		settings_key_press(key, data);
	else if (data->menu->resolution_state == 1)
		resolution_key_press(key, data);
	if (data->menu->game_state == 1)
	{
		if (key == KEY_W)
			data->key_status->w = 1;
		else if (key == KEY_S)
			data->key_status->s = 1;
		else if (key == KEY_A)
			data->key_status->a = 1;
		else if (key == KEY_D)
			data->key_status->d = 1;
		else if (key == KEY_RIGHT)
			data->key_status->right = 1;
		else if (key == KEY_LEFT)
			data->key_status->left = 1;
		else if (key == KEY_M)
		{
			if (data->menu->minimap == 1)
				data->menu->minimap = 0;
			else
				data->menu->minimap = 1;
		}
	}
	if (key == KEY_ESC)
		exit_game(data);
	return (0);
}
/* player_struct modified */
int	key_realese(int key, t_data *data)
{
	if (key == KEY_W  && data->menu->game_state == 1)
		data->key_status->w = 0;
    else if (key == KEY_S && data->menu->game_state == 1)
		data->key_status->s = 0;
    else if (key == KEY_A && data->menu->game_state == 1)
		data->key_status->a = 0;
    else if (key == KEY_D && data->menu->game_state == 1)
		data->key_status->d = 0;
    else if (key == KEY_RIGHT && data->menu->game_state == 1)
		data->key_status->right = 0;
	else if (key ==KEY_LEFT && data->menu->game_state == 1)
		data->key_status->left = 0;
	return (0);
}


int exit_game(t_data *data)
{
    //free
    (void)data;
    clean_exit(data, 0);
	return (0);
}

