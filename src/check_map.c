/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:17:56 by supersko          #+#    #+#             */
/*   Updated: 2022/10/26 15:53:14 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_data *data, int x, int y, int *is_player)
{
	char			c;

	c = data->map[y][x];
	if (c == NORTH)
	{
		data->player->dir.x = 0;
		data->player->dir.y = 1;
	}
	if (c == SOUTH)
	{
		data->player->dir.x = 0;
		data->player->dir.y = -1;
	}
	if (c == EAST)
	{
		data->player->dir.x = -1;
		data->player->dir.y = 0;
	}
	if (c == WEST)
	{
		data->player->dir.x = 1;
		data->player->dir.y = 0;
	}
	data->player->pos_map.x = x;
	data->player->pos_map.y = y;
	//devine plnan
	(*is_player)++;
}

int	is_NSEW(int i, int nb_mapcases)
{
	if (i >= nb_mapcases - 4) //its one of the 4 last map_cases : "01 NSEW"
		return (1);
	else
		return (0);
}

int	is_available_mapcase(t_data *data, int x, int y, int *is_player)
{
	unsigned int	i;
	unsigned int	available_mapcase;
	unsigned int	nb_mapcases;
	char			*mapcases;
	char			c;

	c = data->map[y][x];
	available_mapcase = 0;
	mapcases = ft_strdup(MAPCASES);
	i = 0;
	nb_mapcases = ft_strlen(mapcases);
	while (i < nb_mapcases)
	{
		if (c == mapcases[i])
		{
			if (is_NSEW(i, nb_mapcases))
				init_player(data, x, y, is_player);
			available_mapcase = 1;
			break ;
		}
		i++;
	}
	free(mapcases);
	return (available_mapcase);
}

/* returns TRUE if it has an empty neighourg box */
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

void	check_map_line(t_data *data, int y, int *nb_pers)
{
	int		x;
	int		map_len;
	char	c;

	map_len = ft_matrixlen(data->map);
	x = 0;
	c = data->map[y][0];
	while (c)
	{
		if (!is_available_mapcase(data, x, y, nb_pers))
			exit_msg(data, "[check_map] map contains unavailable char.", -10);
		if (is_border(data, x, y, map_len) && c != WALL)
			exit_msg(data, "[check_map] map not surrounded by walls.", -11);
		c = data->map[y][++x];
	}
}

int	check_map(t_data *data)
{
	int	y;
	int	nb_pers;

	nb_pers = 0;
	y = 0;
	if (!data || !data->map)
		exit_msg(data, "[check_map] map is empty", -1);
	while (data->map[y])
		check_map_line(data, y++, &nb_pers);
	if (nb_pers != 1)
		exit_msg(data, "[check_map] \
				Map does not contains one hero only", -12);
	return (1);
}
