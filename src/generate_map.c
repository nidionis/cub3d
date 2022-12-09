/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:14:23 by dpaulino          #+#    #+#             */
/*   Updated: 2022/12/08 18:14:11 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	generate_map(t_data *data)
{
	int y;
	int x;
	int random;

	x = 1;
	y = 1;
	while (data->map[y] && y != data->map_height - 1)
	{
		while (data->map[y][x] && x != data->map_width - 1)
		{
			random = rand() % 2;
			if (data->map[y][x] != 'E' && data->map[y][x] != 'P')
			{
				if (random == 1)
					data->map[y][x] = '1';
				else if (random == 0)
					data->map[y][x] = '0';
			}
			x++;
		}
		x = 1;
		y++;
	}
	return (1);
}
