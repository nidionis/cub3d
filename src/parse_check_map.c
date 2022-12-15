/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suplayerko <suplayerko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:17:56 by suplayerko          #+#    #+#             */
/*   Updated: 2022/11/19 17:48:55 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_cardinal(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	else
		return (0);
}

int	is_mapcase(t_data *data, char c)
{
	char	*map_cases;

	map_cases = data->map_cases;
	while (*map_cases)
	{
		if (*map_cases == c)
			return (1);
		map_cases++;
	}
	return (0);
}

/* returns TRUE if it has an empty neighourg box
('\0', ' ', or if at the begining of the line */
int	is_border(t_data *data, int x, int y, int matrix_len)
{
	int		last_index_in_line;
	char	**map;

	map = data->map;
	last_index_in_line = (int)ft_strlen(map[y]) - 1;
	if (map[y][x] == EMPTY)
		return (0);
	if (x == 0 || y == 0 \
			|| x == last_index_in_line || y == matrix_len - 1)
		return (1);
	else if (map[y - 1][x] == EMPTY || map[y][x - 1] == EMPTY \
			|| map[y + 1][x] == EMPTY || map[y][x + 1] == EMPTY)
		return (1);
	else if (map[y - 1][x] == '\0' || map[y][x - 1] == '\0' \
			|| map[y + 1][x] == '\0' || map[y][x + 1] == '\0')
		return (1);
	return (0);
}

void	check_map_line(t_data *data, int y, int *nb_player)
{
	int		x;
	int		map_len;
	char	c;

	map_len = ft_matrixlen(data->map);
	x = 0;
	c = data->map[y][0];
	if (is_blank_line(data->map[y]))
		exit_msg(data, "[check_map] map contains blank lines", -10);
	while (c)
	{
		if (!(is_mapcase(data, c) || is_cardinal(c)))
			exit_msg(data, "[check_map] map contains unavailable char.", -10);
		if (is_cardinal(c))
			init_player(data, x, y, nb_player);
		if (is_border(data, x, y, map_len) && c != WALL)
			exit_msg(data, "[check_map] map not surrounded by walls.", -11);
		c = data->map[y][++x];
	}
}

int	check_map(t_data *data)
{
	int	y;
	int	nb_player;

	nb_player = 0;
	y = 0;
	if (!data->map)
		exit_msg(data, "[check_map] map is empty", -1);
	while (data->map[y])
		check_map_line(data, y++, &nb_player);
	if (nb_player != 1)
		exit_msg(data, "[check_map] \
				Map does not contains one hero only", -12);
	format_map(data);
	return (1);
}
