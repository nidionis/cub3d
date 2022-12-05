/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 12:28:19 by dpaulino          #+#    #+#             */
/*   Updated: 2022/12/05 15:23:52 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	key_game(int key, t_data *data)
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
	else if (key == SHIFT)
	{
		if (data->player->speed == 0)
			data->player->speed = 1;
		else
			data->player->speed = 0;
	}
	else if (key == KEY_P)
		printf("open menu\n");
	return (0);
}
