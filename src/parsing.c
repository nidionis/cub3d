/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:17:56 by supersko          #+#    #+#             */
/*   Updated: 2022/10/26 15:09:41 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	import_texture_path( t_data *data, int identifier, char *line)
{
	int	i;

	data->line_split = ft_split(line, ' ');
	if (ft_matrixlen(data->line_split) > 3)
		error_msg("[import_params] WARNING: \
				check .cub file (could be cleaner)");
	i = 1;
	while (data->line_split[i] != NULL && is_blank_line(data->line_split[i]))
		i++;
	if (data->i->texture_path[identifier])
		exit_msg( data, "param identifier must be unique", -1);
	data->i->texture_path[identifier] = ft_strtrim(data->line_split[i], " \n\t");
}

void	import_param( t_data *data, int identifier, char *line)
{
	if (identifier == F)
		data->i->floor_color = init_f_c_color( data, line);
	else if (identifier == C)
		data->i->ceiling_color = init_f_c_color( data, line);
	else
		import_texture_path( data, identifier, line);
}

int	import_params( t_data *data)
{
	int		identifier;
	char	*line;

	line = data->line;
	if (!line)
		return (-1);
	while (is_blank_char(*line))
		line++;
	identifier = get_identifier( data, line);
	//printf("[import], data->line: %s => id: %d\n", data->line, identifier);
	if (identifier == 11) // copying map matrix
		return (1);
	else
		import_param( data, identifier, line);
	ft_free_split(&data->line_split);
	return (0);
}

int	parsing_loop( t_data *data, int *map_parse)
{
	if (!is_blank_line(data->line) || *map_parse)
	{
		if (!*map_parse)
			*map_parse = import_params( data);
		if (*map_parse == 1)
			data->map = ft_append_tab(data->map, ft_strtrim(data->line, "\n"));
	}
	free(data->line);
	return (1);
}

void	init_null( t_data *data, int *map_parse)
{
	int	i;

	*map_parse = 0;
	if ( data)
		data->map = NULL;
	i = 0;
	while (i < NB_TEXTURES)
		data->i->texture_path[i++] = NULL;
	data->i->floor_color = 10;
	data->i->ceiling_color = 10000;
}

void	init_fd( t_data *data, int *fd, char *fname)
{
	file_extention_available( data, fname);
	*fd = open(fname, O_RDONLY);
	if (*fd == -1)
		exit_msg( data, "[init_fd] Error opening file (check file name)", -1);
}

void	file_extention_available( t_data *data, char *fname)
{
	char	*p_ext;

	if (fname)
	{
		p_ext = ft_strnstr(fname, ".cub", ft_strlen(fname));
		if (ft_strlen_char(p_ext, ' ') == 4)
			return ;
	}
	exit_msg( data, "[file_extention_available] only .cub extension", -1);
}

void	parse_file(char *fname, t_data	* data)
{
	int		fd;
	int		map_parse;

	init_null( data, &map_parse);
	init_fd( data, &fd, fname);
	data->line = get_next_line(fd);
	if (data->line)
	{
		while (data->line)
		{
			parsing_loop( data, &map_parse);
			if (map_parse == -1)
				break ;
			data->line = get_next_line(fd);
		}
	}
	close(fd);
	if (map_parse != -1)
		map_parse = check_map( data);
	if (map_parse == -1)
		exit_msg( data, "[parse_file] pb loading map", -1);
}
