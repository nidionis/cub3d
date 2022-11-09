/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suplayerko <suplayerko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:17:56 by suplayerko          #+#    #+#             */
/*   Updated: 2022/10/26 17:33:57 by suplayerko         ###   ########.fr       */
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

char	pix_pos_to_map_case(t_point absolute_pos, char **map)
{
	t_point	map_pos;
	char	c;

	map_pos = pix_pos_to_map_pos(absolute_pos);
	if (absolute_pos.x < 0 || absolute_pos.y < 0)
		c = -1;
	else
		c = map[map_pos.x][map_pos.y];
	return (c);
}
