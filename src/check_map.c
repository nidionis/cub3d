/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <ndionis@student.42mulhouse.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:17:56 by supersko          #+#    #+#             */
/*   Updated: 2022/10/25 20:48:37 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_pers(t_s *s, int x, int y, int *is_pers)
{
	char			c;

	c = s->map[y][x];
	if (c == NORTH)
	{
		s->p->dir.x = 0;
		s->p->dir.y = 1;
	}
	if (c == SOUTH)
	{
		s->p->dir.x = 0;
		s->p->dir.y = -1;
	}
	if (c == EAST)
	{
		s->p->dir.x = -1;
		s->p->dir.y = 0;
	}
	if (c == WEST)
	{
		s->p->dir.x = 1;
		s->p->dir.y = 0;
	}
	s->p->pos_map.x = x;
	s->p->pos_map.y = y;
	//devine plnan
	(*is_pers)++;
}

int	is_NSEW(int i, int nb_mapcases)
{
	if (i >= nb_mapcases - 4) //its one of the 4 last map_cases : "01 NSEW"
		return (1);
	else
		return (0);
}

int	is_available_mapcase(t_s *s, int x, int y, int *is_pers)
{
	unsigned int	i;
	unsigned int	available_mapcase;
	unsigned int	nb_mapcases;
	char			*mapcases;
	char			c;

	c = s->map[y][x];
	available_mapcase = 0;
	mapcases = ft_strdup(MAPCASES);
	i = 0;
	nb_mapcases = ft_strlen(mapcases);
	while (i < nb_mapcases)
	{
		if (c == mapcases[i])
		{
			if (is_NSEW(i, nb_mapcases))
				init_pers(s, x, y, is_pers);
			available_mapcase = 1;
			break ;
		}
		i++;
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
	int		x;
	int		map_len;
	char	c;

	map_len = ft_matrixlen(s->map);
	x = 0;
	c = s->map[y][0];
	while (c)
	{
		if (!is_available_mapcase(s, x, y, nb_pers))
			exit_msg(s, "[check_map] map contains unavailable char.", -10);
		if (is_border(s, x, y, map_len) && c != WALL)
			exit_msg(s, "[check_map] map not surrounded by walls.", -11);
		c = s->map[y][++x];
	}
}

int	check_map(t_s *s)
{
	int	y;
	int	nb_pers;

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
