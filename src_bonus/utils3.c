/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 10:22:48 by dpaulino          #+#    #+#             */
/*   Updated: 2023/01/09 10:37:46 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub3d_bonus.h"

void	set_content_right_values(t_data *data, char **map)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (map[y])
	{
		while (map[y][x])
		{
			if (map[y][x] == '3' && data->switcher.state == 1)
				map[y][x] = '4';
			if (map[y][x] == '5' && data->minimap.state == 1)
				map[y][x] = '1';
			x++;
		}
		y++;
		x = 0;
	}
}
