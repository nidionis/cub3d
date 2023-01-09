/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_interface.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 17:15:14 by dpaulino          #+#    #+#             */
/*   Updated: 2023/01/09 11:43:58 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub3d_bonus.h"

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
	mlx_put_image_to_window(data->window->mlx, data->window->init, \
		data->menu->background[LAYOUT]->img, 750, 889);
	if (data->time_state == 2)
		mlx_string_put(data->window->mlx, data->window->init, \
			data->window->width / 2 - 170, data->window->height - 570 / 2 / 2, \
			rgb_conv(255, 255, 255), str);
	mlx_string_put(data->window->mlx, data->window->init, \
		data->window->width / 2 - 100, data->window->height - pos.y - 1 / 2, \
		rgb_conv(255, 255, 255), "ACTIVATE THE SWITCH TO OPEN THE DOOR");
	free(str);
}
