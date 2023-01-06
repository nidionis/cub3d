/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_interface.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 17:15:14 by dpaulino          #+#    #+#             */
/*   Updated: 2023/01/04 16:06:50 by dpaulino         ###   ########.fr       */
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
	if (data->time_state == 2)
		mlx_string_put(data->window->mlx, data->window->init, \
			data->window->width / 2 - 150, data->window->height - 300 / 2 / 2, \
			rgb_conv(255, 255, 255), str);
	//fprintf(stderr, "[draw interface] height:%d width:%d, pos:%p\n", data->window->height, data->window->width, &pos);
	t_point	i_prompt;
	i_prompt = y_x(data->window->height - pos.y, data->window->width / 2 - pos.x); 
	draw_image(data->img, data->menu->background[LAYOUT], \
	i_prompt, -1);
	mlx_string_put(data->window->mlx, data->window->init, \
		data->window->width / 2 - 50, data->window->height - pos.y / 2, \
		rgb_conv(255, 255, 255), "ACTIVATE THE SWITCH TO OPEN THE DOOR");
	free(str);
}
