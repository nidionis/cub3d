/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_ft.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suplayerko <suplayerko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:17:56 by suplayerko          #+#    #+#             */
/*   Updated: 2022/11/19 18:48:33 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_point	pix_pos_to_map_pos(t_point absolute_pos)
{
	t_point	map_pos;
	int		u;

	u = (int)UNITS_PER_BOX;
	if (absolute_pos.x < 0 || absolute_pos.y < 0)
		fprintf(stderr, "[pix_pos_to_map_pos] absolute_pos = {%d, %d} but cannot contain negative numbers\n", absolute_pos.x, absolute_pos.y);
	map_pos.x = absolute_pos.x / u;
	map_pos.y = absolute_pos.y / u;
	return (map_pos);
}

char	pix_pos_to_map_case(t_data *data, t_point absolute_pos)
{
	t_point	map_pos;
	char	c;
	char	**map;

	map = data->map;
	map_pos = pix_pos_to_map_pos(absolute_pos);
	if (still_in_map(data, absolute_pos))
		c = map[map_pos.y][map_pos.x];
	else
		c = -1;
	return (c);
}

/* check if point is not outside */
int	still_in_map(t_data *data, t_point pt)
{
	if (pt.x < 0 || pt.x >= data->map_size_in_units[_x])
		return (0);
	if (pt.y < 0 || pt.y >= data->map_size_in_units[_y])
		return (0);
	return (1);
}

