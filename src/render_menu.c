/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_menu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 10:43:23 by dpaulino          #+#    #+#             */
/*   Updated: 2022/12/15 12:29:04 by dpaulino         ###   ########.fr       */
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
	static int counter;
	int width;
	t_img_data **bg;
	bg = data->menu->background;
	width = data->window->width / 2 - bg[NEW_GAME]->width / 2;
	counter++;
	if (counter == 1)
	{
		if (data->menu->menu_state == 1)
		{
			draw_image(bg[BG],bg[NEW_GAME],y_x(30, width),rgb_conv(rand() % 150,rand() % 150,rand() % 150));
			draw_image(bg[BG],bg[CONTROLS],y_x(130, width),rgb_conv(rand() % 150,rand() %150,rand() % 150));
			draw_image(bg[BG],bg[EXTRAS],y_x(230, width),rgb_conv(rand() % 150,rand() %150,rand() % 150));
			draw_image(bg[BG],bg[SETTINGS],y_x(330,width),rgb_conv(rand() % 150,rand() % 150,rand() % 150));
			draw_image(bg[BG],bg[EXIT],y_x(430, width),rgb_conv(rand() % 150,rand() %150,rand() % 150));
		}
		else if(data->menu->settings_state == 1)
		{
			draw_image(bg[BG],bg[RESOLUTION],y_x(30,width),rgb_conv(rand() % 150,rand() % 150,rand() % 150));
			draw_image(bg[BG],bg[SENSIVITY],y_x(130,width),rgb_conv(rand() % 150,rand() % 150,rand() % 150));
			draw_image(bg[BG],bg[BACK],y_x(230,width),rgb_conv(rand() % 150,rand() % 150,rand() % 150));
		}
	}
	if (counter == 50)
	{
		if (data->menu->menu_state == 1)
		{
			draw_image(bg[BG],bg[NEW_GAME],y_x(30,width),rgb_conv(rand() % 150,rand() % 150,rand() % 150));
			draw_image(bg[BG],bg[CONTROLS],y_x(130,width),rgb_conv(rand() % 150,rand() % 150,rand() % 150));
			draw_image(bg[BG],bg[EXTRAS],y_x(230,width),rgb_conv(rand() % 150,rand() % 150,rand() % 150));
			draw_image(bg[BG],bg[SETTINGS],y_x(330,width),rgb_conv(rand() % 150,rand() % 150,rand() % 150));
			draw_image(bg[BG],bg[EXIT],y_x(430,width),rgb_conv(rand() % 150,rand() % 150,rand() % 150));
		}
		else if (data->menu->settings_state == 1)
		{
			draw_image(bg[BG],bg[RESOLUTION],y_x(30,width),rgb_conv(rand() % 150,rand() % 150,rand() % 150));
			draw_image(bg[BG],bg[SENSIVITY],y_x(130,width),rgb_conv(rand() % 150,rand() % 150,rand() % 150));
			draw_image(bg[BG],bg[BACK],y_x(230,width),rgb_conv(rand() % 150,rand() % 150,rand() % 150));
		}
		else if (data->menu->resolution_state == 1)
		{
			draw_image(bg[BG],bg[HIGH_RES],y_x(30,width),rgb_conv(rand() % 150,rand() % 150,rand() % 150));
			draw_image(bg[BG],bg[MID_RES],y_x(130,width),rgb_conv(rand() % 150,rand() % 150,rand() % 150));
			draw_image(bg[BG],bg[LOW_RES],y_x(230,width),rgb_conv(rand() % 150,rand() % 150,rand() % 150));
			draw_image(bg[BG],bg[BACK],y_x(330,width),rgb_conv(rand() % 150,rand() % 150,rand() % 150));
		}
		counter = 0;
	}
	if (data->menu->new_game == 1)
		draw_image(bg[BG], bg[NEW_GAME],y_x(30,width),data->menu->highlight);
	if (data->menu->controls == 1)
		draw_image(bg[BG], bg[CONTROLS],y_x(130,width),data->menu->highlight);
	if (data->menu->extras == 1)
		draw_image(bg[BG], bg[EXTRAS],y_x(230,width),data->menu->highlight);
	if (data->menu->settings == 1)
		draw_image(bg[BG], bg[SETTINGS],y_x(330,width),data->menu->highlight);
	if (data->menu->quit == 1)
		draw_image(bg[BG], bg[EXIT],y_x(430,width),data->menu->highlight);
	//seting
	if (data->menu->resolution == 1)
		draw_image(bg[BG],bg[RESOLUTION],y_x(30,width),data->menu->highlight);
	if (data->menu->sensivity == 1)
		draw_image(bg[BG],bg[SENSIVITY],y_x(130,width),data->menu->highlight);
	if (data->menu->back == 1)
		draw_image(bg[BG],bg[BACK],y_x(230,width),data->menu->highlight);
		//res
	if (data->menu->high_res == 1)
		draw_image(bg[BG],bg[HIGH_RES],y_x(30,width),data->menu->highlight);
	if (data->menu->mid_res == 1)
		draw_image(bg[BG],bg[MID_RES],y_x(130,width),data->menu->highlight);
	if (data->menu->low_res == 1)
		draw_image(bg[BG],bg[LOW_RES],y_x(230,width),data->menu->highlight);
	mlx_put_image_to_window(data->window->mlx, data->window->init,data->menu->background[0]->img, 0, 0);
	return(0);
}