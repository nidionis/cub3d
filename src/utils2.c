/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 02:41:23 by dpaulino          #+#    #+#             */
/*   Updated: 2023/01/04 17:45:32 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	get_res_height(void)
{
	int	height;

	height = SCREEN_HEIGHT;
	return (height);
}

int	get_res_width(void)
{
	int	width;

	width = SCREEN_WIDTH;
	return (width);
}

int	is_block(t_data *data, char c)
{
	int		i;
	char	*blocks;

	blocks = data->blocks;
	i = 0;
	while (blocks[i])
	{
		if (c == blocks[i])
			return (i);
		i++;
	}
	return (-1);
}

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
