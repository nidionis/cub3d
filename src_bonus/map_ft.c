/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_ft.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:17:56 by suplayerko        #+#    #+#             */
/*   Updated: 2023/01/04 16:48:46 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub3d_bonus.h"

t_point	pix_pos_to_map_pos(t_point absolute_pos)
{
	t_point	map_pos;
	int		u;

	u = (int)UNITS_PER_BOX;
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

int	still_in_map(t_data *data, t_point pt)
{
	if (pt.x < 0 || pt.x >= data->map_size_in_units[_x])
		return (0);
	if (pt.y < 0 || pt.y >= data->map_size_in_units[_y])
		return (0);
	return (1);
}
