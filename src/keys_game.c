/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 12:28:19 by dpaulino          #+#    #+#             */
/*   Updated: 2022/12/13 11:42:43 by dpaulino         ###   ########.fr       */
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
		if (data->player->speed == 0 && data->player->stamina > 5)
			data->player->speed = 1;
		else
			data->player->speed = 0;
	}
	else if (key == KEY_P)
		data->map[0][1] = '0';
	if (end_game(data,&data->door) && key == KEY_E && data->switcher.state == 1)
	{
		Mix_HaltChannel(-1);
			SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
		Mix_Chunk *sound = Mix_LoadWAV("gameover.wav");
		Mix_PlayChannel(-1, sound, 0);
		// exit(0);
	}
	if (end_game(data,&data->switcher) && key == KEY_E && data->switcher.state == 0)
	{
		data->switcher.state = 1;
	}
	if (end_game(data,&data->minimap) && key == KEY_E && data->minimap.state == 0)
	{
		data->minimap.state = 1;
	}
	return (0);
}
