/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_interface.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 17:15:14 by dpaulino          #+#    #+#             */
/*   Updated: 2023/01/04 17:42:25 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_point	get_string_pos(void)
{
	t_point	pos;

	pos.y = 125;
	pos.x = 200;
	return (pos);
}

void	draw_interface(t_data *data)
{
	t_point	pos;
	char	*str;

	pos = get_string_pos();
	str = ft_itoa(time(NULL) - data->time_to_lose);
	if (data->time_state == 2)
		mlx_string_put(data->window->mlx, data->window->init, \
			data->window->width / 2 - 150, data->window->height - 300 / 2 / 2, \
			rgb_conv(255, 255, 255), str);
	draw_image(data->img, data->menu->background[LAYOUT], \
	y_x(data->window->height - pos.y, data->window->width / 2 - pos.x), -1);
	mlx_string_put(data->window->mlx, data->window->init, \
		data->window->width / 2 - 50, data->window->height - pos.y / 2, \
		rgb_conv(255, 255, 255), "ACTIVATE THE SWITCH TO OPEN THE DOOR");
	free(str);
}
