/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_menu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 10:43:23 by dpaulino          #+#    #+#             */
/*   Updated: 2022/12/02 10:56:24 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	render_menu(t_data *data)
{
	t_point	pos[3];

	pos[0].x = 600;
	pos[0].y = 380;
	pos[1].x = 680;
	pos[1].y = 50;
	pos[2].x = 680;
	pos[2].y = 700;
	draw_image(data->menu->background[0],data->menu->background[1],pos[0],rgb_conv(200,0,0));
	draw_image(data->menu->background[0],data->menu->background[2],pos[1],0);
	draw_image(data->menu->background[0],data->menu->background[3],pos[2],0);
	mlx_put_image_to_window(data->window->mlx, data->window->init,data->menu->background[0]->img, 0, 0);
}