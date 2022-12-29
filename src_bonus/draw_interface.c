/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_interface.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 17:15:14 by dpaulino          #+#    #+#             */
/*   Updated: 2022/12/17 17:41:07 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_interface(t_data *data)
{
	int	y;
	int	x;

	x = 0;
	y = 0;
	if (g_status == 1)
	{
		x = 300;
		y = 195;
	}
	else if (g_status == 2)
	{
		y = 125;
		x = 200;
	}
	else if (g_status == 3)
	{
		x = 200;
		y = 130;
	}
	draw_image(data->img, data->menu->background[LAYOUT], \
	y_x(data->window->height - y, data->window->width / 2 - x), -1);
}
