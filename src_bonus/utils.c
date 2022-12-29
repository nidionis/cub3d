/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 04:23:36 by dpaulino          #+#    #+#             */
/*   Updated: 2022/12/21 15:21:04 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_point	y_x(int y, int x)
{
	t_point	tmp;

	tmp.x = x;
	tmp.y = y;
	return (tmp);
}

void	get_map_size(t_data *data)
{
	int	i;

	i = 0;
	data->map_width = ft_strlen(data->map[0]);
	while (data->map[i])
	{
		i++;
	}
	data->map_height = i;
}

int	set_red_to_max(int color)
{
	int	r;
	int	g;
	int	b;

	r = (color >> 16) & 0xff;
	g = (color >> 8) & 0xff;
	b = color & 0xff;
	r = 255;
	return ((r << 16) | (g << 8) | b);
}

//change all pixels of a img to red
void	change(t_data *data, t_img_data *img)
{
	int	i;

	i = 1;
	(void)data;
	while (i < data->window->width * data->window->height - 1)
	{
		img->address[i] = set_red_to_max(img->address[i]);
		i++;
	}
}

int	set_black_to_max(int color)
{
	int	r;
	int	g;
	int	b;

	r = (color >> 16) & 0xff;
	g = (color >> 8) & 0xff;
	b = color & 0xff;
	r = 0;
	return ((r << 16) | (g << 8) | b);
}

void	change_to_black(t_data *data, t_img_data *img)
{
	int	i;

	i = 1;
	(void)data;
	while (i < data->window->width * data->window->height - 1)
	{
		img->address[i] = set_black_to_max(img->address[i]);
		i++;
	}
}

char	**alloc_mem(int size_y, int size_x)
{
	int		i;
	char	**map;

	i = 0;
	map = ft_calloc((size_y), sizeof(char *) + 1);
	while (i < size_y)
	{
		map[i] = ft_calloc((size_x), sizeof(char) + 1);
		i++;
	}
	return (map);
}
