/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 14:57:02 by dpaulino          #+#    #+#             */
/*   Updated: 2022/11/02 18:33:22 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int fix_ang(int a)
{ if(a>359)
	{
		a-=360;
	}
	if(a<0)
	{
		a+=360;
	}
	return a;
}

int	key_event(int key, t_data *data)
{
	t_player *player;

	player = data->player;
	if (key == KEY_W)
	{
		printf("player move up\n");
		move_player(data, FORWARD);
	}
    else if (key == KEY_S)
	{
		printf("player move down\n");
		move_player(data, BACKWARD);
	}
    else if (key == KEY_A)
	{
		move_player(data, LEFT);
		printf("player move left\n");
	}
    else if (key == KEY_D)
	{
		move_player(data, RIGHT);
		printf("player move right\n");
	}
    else if (key == KEY_RIGHT)
    {
		printf("player rotate right\n");
		rotate_player(data->player, RIGHT);
    }
	else if (key ==KEY_LEFT)
    {
		printf("player rotate left\n");
		rotate_player(data->player, LEFT);
    }
    mlx_clear_window(data->window->mlx, data->window->init);
	return (0);
}

int exit_game(t_data *data)
{
    //free
    (void)data;
    clean_exit(data, 0);
}

