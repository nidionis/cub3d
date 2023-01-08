/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 12:28:19 by dpaulino          #+#    #+#             */
/*   Updated: 2023/01/04 18:51:28 by dpaulino         ###   ########.fr       */
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

void	controls(t_data *data, int key)
{
	if (key == KEY_M)
	{
		if (data->menu->minimap == 1)
			data->menu->minimap = 0;
		else
			data->menu->minimap = 1;
	}
}

int	key_game(int key, t_data *data)
{
	movement(data, key);
	return (0);
}
