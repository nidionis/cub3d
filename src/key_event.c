/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 14:57:02 by dpaulino          #+#    #+#             */
/*   Updated: 2022/11/23 15:51:09 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void            my_mlx_pixel_put(t_img_data *img, int x, int y, int color)
{
  char    *dst;

  dst = img->adress + (y * img->line_len + x * (img->bpp / 8));
  *(unsigned int*)dst = color;
}

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

int	key_event2(int key, t_data *data)
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
    {
		data->key_status->right = 1;
    }
	else if (key ==KEY_LEFT)
    {
		data->key_status->left = 1;
    }
	return (0);
}
/* player_struct modified */
int	key_event(int key, t_data *data)
{
	if (key == KEY_W)
	{
		data->key_status->w = 0;
	}
    else if (key == KEY_S)
	{
		data->key_status->s = 0;
	}
    else if (key == KEY_A)
	{
		data->key_status->a = 0;
	}
    else if (key == KEY_D)
	{
		data->key_status->d = 0;
	}
    else if (key == KEY_RIGHT)
    {
		data->key_status->right = 0;
    }
	else if (key ==KEY_LEFT)
    {
		data->key_status->left = 0;
    }
	return (0);
}


int exit_game(t_data *data)
{
    //free
    (void)data;
    clean_exit(data, 0);
	return (0);
}

