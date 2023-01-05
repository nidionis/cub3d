/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_menu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 10:43:23 by dpaulino          #+#    #+#             */
/*   Updated: 2023/01/04 17:45:18 by dpaulino         ###   ########.fr       */
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

static void	menu_highlight(t_data *data, t_img_data **bg, t_point *pos, \
		int width)
{
	if (data->menu->new_game == 1)
		draw_image(bg[BG], bg[NEW_GAME], y_x(pos->y - 300, width), \
				data->menu->highlight);
	if (data->menu->controls == 1)
		draw_image(bg[BG], bg[CONTROLS], y_x(pos->y - 200, width), \
				data->menu->highlight);
	if (data->menu->extras == 1)
		draw_image(bg[BG], bg[EXTRAS], y_x(pos->y - 100, width), \
				data->menu->highlight);
	if (data->menu->quit == 1)
		draw_image(bg[BG], bg[EXIT], y_x(pos->y, width), \
				data->menu->highlight);
	if (data->menu->back == 1)
		draw_image(bg[BG], bg[BACK], y_x(pos->y, width), \
				data->menu->highlight);
	mlx_put_image_to_window(data->window->mlx, data->window->init, \
			data->menu->background[0]->img, 0, 0);
}

static int	rand_bg_color(t_data *data, t_img_data **bg, \
		t_point *pos, int width)
{
	if (data->menu->menu_state == 1)
	{
		draw_image(bg[BG], bg[NEW_GAME], y_x(pos->y - 300, width), \
				rgb_conv(rand() % 150, rand() % 150, rand() % 150));
		draw_image(bg[BG], bg[CONTROLS], y_x(pos->y - 200, width), \
				rgb_conv(rand() % 150, rand() % 150, rand() % 150));
		draw_image(bg[BG], bg[EXTRAS], y_x(pos->y - 100, width), \
				rgb_conv(rand() % 150, rand() % 150, rand() % 150));
		draw_image(bg[BG], bg[EXIT], y_x(pos->y, width), \
				rgb_conv(rand() % 150, rand() % 150, rand() % 150));
	}
	return (0);
}

int	render_menu(t_data *data)
{
	static int	counter;
	int			width;
	t_img_data	**bg;
	t_point		pos;

	pos.y = 430;
	bg = data->menu->background;
	width = data->window->width / 2 - bg[NEW_GAME]->width / 2;
	counter++;
	if (counter == 1)
		rand_bg_color(data, bg, &pos, width);
	if (counter == 50)
		counter = rand_bg_color(data, bg, &pos, width);
	menu_highlight(data, bg, &pos, width);
	return (0);
}
