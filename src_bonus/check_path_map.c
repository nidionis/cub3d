/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 10:08:34 by dpaulino          #+#    #+#             */
/*   Updated: 2023/01/02 12:53:55 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub3d_bonus.h"

int	back_track_map(t_data *data, char **map, int row, int col)
{
	if (map[row][col] == '5')
		return (1);
	else if (map[row][col] == '0' || map[row][col] == 'E' || \
		map[row][col] == 'N' || map[row][col] == 'W' \
			|| map[row][col] == 'S')
	{
		map[row][col] = 'X';
		if (row < data->map_height)
			if (back_track_map(data, map, row + 1, col))
				return (1);
		if (row > 0)
			if (back_track_map(data, map, row - 1, col))
				return (1);
		if (col < data->map_width)
			if (back_track_map(data, map, row, col + 1))
				return (1);
		if (col > 0)
			if (back_track_map(data, map, row, col - 1))
				return (1);
		map[row][col] = 'Y';
	}
	return (0);
}

int	check_path_map(t_data *data, int row, int col)
{
	char	**map;
	int		y;
	int		x;
	int		status;

	x = 0;
	y = 0;
	if (data->minimap.state == 1)
		return (1);
	map = ft_calloc(data->map_height + 1, sizeof(char *));
	while (data->map[y])
	{
		map[y] = ft_calloc(data->map_width + 1, sizeof(char));
		while (data->map[y][x])
		{
			map[y][x] = data->map[y][x];
			x++;
		}
		x = 0;
		y++;
	}
	status = back_track_map(data, map, row, col);
	ft_free_split(&map);
	return (status);
}
