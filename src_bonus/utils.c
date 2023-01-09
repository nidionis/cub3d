/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 04:23:36 by dpaulino          #+#    #+#             */
/*   Updated: 2023/01/09 11:21:04 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub3d_bonus.h"

int	set_red_to_max(int color)
{
	int	r;
	int	g;
	int	b;

	r = (color >> 16) & 0xff;
	g = (color >> 8) & 0xff;
	b = color & 0xff;
	r = 240;
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
	map = ft_calloc((size_y), sizeof(char *) + 2);
	while (i < size_y)
	{
		map[i] = ft_calloc((size_x), sizeof(char) + 1);
		i++;
	}
	return (map);
}
