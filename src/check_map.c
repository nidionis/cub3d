/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <ndionis@student.42mulhouse.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:17:56 by supersko          #+#    #+#             */
/*   Updated: 2022/10/25 12:54:55 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_available_mapcase(char c, int *is_pers)
{
	unsigned int	i;
	unsigned int	available_mapcase;
	unsigned int	nb_mapcases;
	char			*mapcases;

	available_mapcase = 0;
	mapcases = ft_strdup(MAPCASES);
	i = 0;
	nb_mapcases = ft_strlen(mapcases);
	while (i < nb_mapcases)
	{
		if (c == mapcases[i++])
		{
			available_mapcase = 1;
			break ;
		}
		if (i >= nb_mapcases - 4)
			*is_pers += 1;
	}
	free(mapcases);
	return (available_mapcase);
}

int	is_border(t_s *s, int x, int y, int matrix_len)
{
	if (s->map[y][x] == EMPTY)
		return (0);
	if (x == 0 || y == 0 \
			|| x == (int)ft_strlen(s->map[y]) - 1 || y == matrix_len - 1)
		return (1);
	else if (s->map[y - 1][x] == EMPTY || s->map[y][x - 1] == EMPTY \
			|| s->map[y + 1][x] == EMPTY || s->map[y][x + 1] == EMPTY)
		return (1);
	else if (s->map[y - 1][x] == '\0' || s->map[y][x - 1] == '\0' \
			||s->map[y + 1][x] == '\0' || s->map[y][x + 1] == '\0')
		return (1);
	return (0);
}

void	check_map_line(t_s *s, int y, int *nb_pers)
{
	int	x;

	x = 0;
	while (s->map[y][x])
	{
		if (!is_available_mapcase(s->map[y][x], nb_pers))
			exit_msg(s, "[check_map] map contains unavailable char.", -10);
		if (is_border(s, x, y, ft_matrixlen(s->map)) && s->map[y][x] != WALL)
			exit_msg(s, "[check_map] map not surrounded by walls.", -11);
		x++;
	}
}

int	check_map(t_s *s)
{
	int	y;
	int	matrix_len;
	int	nb_pers;

	matrix_len = ft_matrixlen(s->map);
	nb_pers = 0;
	y = 0;
	if (!s || !s->map)
		exit_msg(s, "[check_map] map is empty", -1);
	while (s->map[y])
		check_map_line(s, y++, &nb_pers);
	if (nb_pers != 1)
		exit_msg(s, "[check_map] \
				Map does not contains one hero only", -12);
	return (1);
}
