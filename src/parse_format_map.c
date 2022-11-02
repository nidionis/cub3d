/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suplayerko <suplayerko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:17:56 by suplayerko          #+#    #+#             */
/*   Updated: 2022/10/26 17:51:25 by suplayerko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	shift_line_left(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i + 1])
	{
		line[i] = line[i + 1];
		i++;
	}
	line[i] = '0';
}

void	delete_first_column(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		shift_line_left(map[i++]);
}

int	is_first_column_empty(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (!is_blank_char(map[i][0]))
			return (0);
		i++;
	}
	return (1);
}

/* delete an a column of EMPTY at left side of map */
void	clean_useless_empty_splace(char	**map)
{
	while (is_first_column_empty(map))
		delete_first_column(map);
}

int	get_map_width(char **map)
{
	int	width;

	width = (int)ft_strlen(*map++);
	while (*map)
	{
		if ((int)ft_strlen(*map) > width)
			width = (int)ft_strlen(*map);
		map++;
	}
	return (width);
}

/* line passed by reference */
void	complete_line_to_width(t_data *data, char **line, int len)
{
	char	*tmp_line;
	int		i;

	tmp_line = malloc(len + 1);
	if (!tmp_line)
		exit_msg(data, "[complete_line_to_width] malloc error", -1);
	tmp_line[len] = '\0';
	i = 0;
	while ((*line)[i])
	{
		tmp_line[i] = (*line)[i];
		i++;
	}
	while (i < len)
		tmp_line[i++] = EMPTY;
	free(*line);
	*line = NULL;
	*line = tmp_line;
}

void	rectangle_map(t_data *data, char **map)
{
	int 	map_width;
	int		i;

	i = 0;
	map_width = get_map_width(map);
	while (map[i])
	{
		if ((int)ft_strlen(map[i]) < map_width)
			complete_line_to_width(data, &map[i], map_width);
		i++;
	}
}

void	format_map(t_data *data)
{
	char	**map;

	if (data->map == NULL)
		exit_msg(data, "[format_map] map disapear (existed in check_param_missing", -1);
	map = data->map;
	clean_useless_empty_splace(map);
	rectangle_map(data, map);
}
