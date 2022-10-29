/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_import.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:17:56 by supersko          #+#    #+#             */
/*   Updated: 2022/10/26 18:17:51 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	import_texture_path(t_data *data, int identifier, char *line)
{
	int	i;

	data->line_split = ft_split(line, ' ');
	if (ft_matrixlen(data->line_split) > 3)
		error_msg("[import_params] WARNING: \
				check .cub file (could be cleaner)");
	i = 1;
	while (data->line_split[i] != NULL && is_blank_line(data->line_split[i]))
		i++;
	if (data->image->texture_path[identifier])
		exit_msg(data, "param identifier must be unique", -1);
	data->image->texture_path[identifier] = ft_strtrim(data->line_split[i], " \n\t");
}

void	import_param(t_data *data, int identifier, char *line)
{
	if (identifier == F)
		data->image->floor_color = init_f_c_color(data, line);
	else if (identifier == C)
		data->image->ceiling_color = init_f_c_color(data, line);
	else
		import_texture_path(data, identifier, line);
}

int	import_params(t_data *data)
{
	int		identifier;
	char	*line;

	line = data->line;
	if (!line)
		return (-1);
	while (is_blank_char(*line))
		line++;
	identifier = get_identifier(data, line);
	//printf("[import], data->line: %s => id: %d\n", data->line, identifier);
	if (identifier == 11) // copying map matrix
		return (1);
	else
		import_param(data, identifier, line);
	ft_free_split(&data->line_split);
	return (0);
}

int	parsing_loop(t_data *data, int *map_parse)
{
	if (!is_blank_line(data->line) || *map_parse)
	{
		if (!*map_parse)
			*map_parse = import_params(data);
		if (*map_parse == 1)
			data->map = ft_append_tab(data->map, ft_strtrim(data->line, "\n"));
	}
	free(data->line);
	return (1);
}

void	parse_file(char *fname, t_data	*data)
{
	int		fd;
	int		map_parse;

	init_null(data, &map_parse);
	init_fd(data, &fd, fname);
	data->line = get_next_line(fd);
	if (data->line)
	{
		while (data->line)
		{
			parsing_loop(data, &map_parse);
			if (map_parse == -1)
				break ;
			data->line = get_next_line(fd);
		}
	}
	close(fd);
	if (map_parse != -1)
		map_parse = check_map(data);
	if (map_parse == -1)
		exit_msg(data, "[parse_file] pb loading map", -1);
}
