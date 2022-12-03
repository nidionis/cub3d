/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_menu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 10:43:23 by dpaulino          #+#    #+#             */
/*   Updated: 2022/12/03 05:04:54 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	render_menu(t_data *data)
{
	t_point	pos[4];
	static int counter;
	pos[0].x = 600;
	pos[0].y = 380;
	pos[1].x = 680;
	pos[1].y = 50;
	pos[2].x = 680;
	pos[2].y = 700;
	counter++;
	if (counter == 1)
	{
		draw_image(data->menu->background[0],data->menu->background[1],pos[0],rgb_conv(rand() % 150,rand() % 150,rand() % 150));
		draw_image(data->menu->background[0],data->menu->background[2],pos[1],rgb_conv(rand() % 150,rand() % 150,rand() % 150));
		draw_image(data->menu->background[0],data->menu->background[3],pos[2],rgb_conv(rand() % 150,rand() %150,rand() % 150));
	}
	if (counter == 100)
	{
		draw_image(data->menu->background[0],data->menu->background[1],pos[0],rgb_conv(rand() % 150,rand() % 150,rand() % 150));
		draw_image(data->menu->background[0],data->menu->background[2],pos[1],rgb_conv(rand() % 150,rand() % 150,rand() % 150));
		draw_image(data->menu->background[0],data->menu->background[3],pos[2],rgb_conv(rand() % 150,rand() % 150,rand() % 150));
		draw_image(data->menu->background[0], data->menu->background[5],y_x(50, 100), rgb_conv(rand() % 150,rand() % 150,rand() % 150));
		draw_image(data->menu->background[0], data->menu->background[5],y_x(600, 1400), rgb_conv(rand() % 150,rand() % 150,rand() % 150));
		counter = 0;
	}
	if (data->menu->options == 1)
		draw_image(data->menu->background[0],data->menu->background[1],pos[0],data->menu->highlight);
	if (data->menu->quit == 1)
		draw_image(data->menu->background[0],data->menu->background[3],pos[2],data->menu->highlight);
	if (data->menu->start == 1)
		draw_image(data->menu->background[0],data->menu->background[2],pos[1],data->menu->highlight);
	mlx_put_image_to_window(data->window->mlx, data->window->init,data->menu->background[0]->img, 0, 0);
	return(0);
}