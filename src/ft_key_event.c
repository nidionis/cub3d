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
		player->pos_box.x += player->direction.x * 2;
		player->pos_box.y += player->direction.y * 2;
	}
    else if (key == KEY_S)
	{
		printf("player move down\n");
		player->pos_box.x -= player->direction.x * 2;
		player->pos_box.y -= player->direction.y * 2;
	}
    else if (key == KEY_A)
	{
		printf("nono\n");
	}
    else if (key == KEY_D)
	{
		printf("nono\n");
	}
    else if (key == KEY_RIGHT)
    {
		printf("player move left\n");
		player->angle -= 5;
		player->angle = fix_ang(player->angle);
		player->direction.x = cos(degree_to_radian(player->angle)) * 5;
		player->direction.y = -sin(degree_to_radian(player->angle)) * 5;
    }
	else if (key ==KEY_LEFT)
    {
		printf("player move right\n");
		player->angle += 5;
		player->angle = fix_ang(player->angle);
		player->direction.x = cos(degree_to_radian(player->angle)) * 5;
		player->direction.y = -sin(degree_to_radian(player->angle)) * 5;
		
    }
    mlx_clear_window(data->window->mlx, data->window->init);
	return (0);
}

int exit_game(t_data *data)
{
    //free
    (void)data;
    exit(0);
}

