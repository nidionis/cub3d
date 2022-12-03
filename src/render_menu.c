/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_menu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 10:43:23 by dpaulino          #+#    #+#             */
/*   Updated: 2022/12/03 18:52:42 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
//turn every pixel in image to black
void	clear_img(t_img_data *img)
{
	int	i;

	i = 0;
	while (i < img->height * img->width)
	{
			img->address[i] = 0;
		i++;
	}
}

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
	if (data->menu->options == 1 && data->menu->on == 1)
	{
		clear_img(data->menu->background[0]);
		draw_image(data->menu->background[0],data->menu->background[11],y_x(0,0),-1);
		draw_image(data->menu->background[0],data->menu->background[8],y_x(100, SCREEN_WIDTH/2 - data->menu->background[7]->width/2),-1);
		draw_image(data->menu->background[0],data->menu->background[9],y_x(400,SCREEN_WIDTH/2 - data->menu->background[7]->width/2),-1);
		draw_image(data->menu->background[0],data->menu->background[10],y_x(700,SCREEN_WIDTH/2 - data->menu->background[7]->width/2),-1);
	}
	mlx_put_image_to_window(data->window->mlx, data->window->init,data->menu->background[0]->img, 0, 0);
	return(0);
}