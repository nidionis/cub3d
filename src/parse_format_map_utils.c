/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_format_map_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 16:27:53 by dpaulino          #+#    #+#             */
/*   Updated: 2023/01/04 17:44:21 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	shift_line_left(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i + 1])
	{
		line[i] = line[i + 1];
		i++;
	}
	line[i] = '\0';
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
