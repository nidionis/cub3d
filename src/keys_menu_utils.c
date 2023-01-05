/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_menu_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 10:54:50 by dpaulino          #+#    #+#             */
/*   Updated: 2023/01/04 17:43:15 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_menu_controls(t_data *data)
{
	if (data->window->width == 1900)
		draw_image(data->menu->background[BG], \
		data->menu->background[CONTROLS_KEYS], \
			y_x(300, 100), rgb_conv(rand() % 155, rand() % 155, rand() % 155));
	else if (data->window->width == 1200)
		draw_image(data->menu->background[BG], \
		data->menu->background[CONTROLS_KEYS], \
			y_x(50, 300), rgb_conv(rand() % 155, rand() % 155, rand() % 155));
	else
		draw_image(data->menu->background[BG], \
		data->menu->background[CONTROLS_KEYS], \
			y_x(0, 0), rgb_conv(rand() % 155, rand() % 155, rand() % 155));
}

void	draw_menu_extras(t_data *data)
{
	draw_image(data->menu->background[BG], data->menu->background[10], \
		y_x(300, 100), rgb_conv(rand() % 155, rand() % 155, rand() % 155));
}
