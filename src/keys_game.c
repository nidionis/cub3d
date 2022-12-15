/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 12:28:19 by dpaulino          #+#    #+#             */
/*   Updated: 2022/12/15 03:39:30 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	movement(t_data *data, int key)
{
	if (key == KEY_W)
		data->key_status->w = 1;
	if (key == KEY_S)
		data->key_status->s = 1;
	if (key == KEY_A)
		data->key_status->a = 1;
	if (key == KEY_D)
		data->key_status->d = 1;
	if (key == KEY_RIGHT)
		data->key_status->right = 1;
	if (key == KEY_LEFT)
		data->key_status->left = 1;
}

void controls(t_data *data, int key)
{
	if (key == KEY_M)
	{
		if (data->menu->minimap == 1)
			data->menu->minimap = 0;
		else
			data->menu->minimap = 1;
	}
	if (key == SHIFT)
	{
		if (data->player->speed == 0 && data->player->stamina > 5)
			data->player->speed = 1;
		else
			data->player->speed = 0;
	}
	if (key == KEY_P)
	{
		if (data->menu->game_state == 1)
			data->menu->game_state = 0;
		else
			data->menu->game_state = 1;
	}
}

int	key_game(int key, t_data *data)
{
	movement(data, key);
	controls(data, key);
	if (end_game(data, &data->door) && key == KEY_E && \
	data->switcher.state == 1)
	{
		exit(0);
	}
	if (end_game(data, &data->switcher) && key == KEY_E \
	&& data->switcher.state == 0)
	{
		data->switcher.state = 1;
	}
	if (end_game(data, &data->minimap) && key == KEY_E && \
	data->minimap.state == 0)
		data->minimap.state = 1;
	return (0);
}
