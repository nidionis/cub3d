/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   soundtracks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 19:44:20 by dpaulino          #+#    #+#             */
/*   Updated: 2023/01/02 12:57:45 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub3d_bonus.h"

// int	load_soundtrack(t_data *data, t_audio *audio, char *path)
// {
// 	(void)data;
// 	SDL_LoadWAV(path, &audio->wavSpec, &audio->wavBuffer, &audio->wavLength);
// 	return (0);
// }

// int	play_soundtrack(t_data *data, t_audio *audio)
// {
// 	SDL_Init(SDL_INIT_AUDIO);
// 	data->audio_dev = SDL_OpenAudioDevice(NULL, 0, &audio->wavSpec, NULL, 0);
// 	SDL_QueueAudio(data->audio_dev, audio->wavBuffer, audio->wavLength);
// 	SDL_PauseAudioDevice(data->audio_dev, 0);
// 	return (0);
// }

// int	stop_soundtrack(t_data *data, t_audio *audio)
// {
// 	SDL_CloseAudioDevice(data->audio_dev);
// 	SDL_FreeWAV(audio->wavBuffer);
// 	SDL_Quit();
// 	return(0);
// }
