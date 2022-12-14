/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_import.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:17:56 by supersko          #+#    #+#             */
/*   Updated: 2022/12/12 01:39:34 by dpaulino         ###   ########.fr       */
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
	data->image->texture_path[identifier] = \
		ft_strtrim(data->line_split[i], " \n\t");
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
	if (identifier == 11)
		return (1);
	else
		import_param(data, identifier, line);
	ft_free_split(&data->line_split);
	return (0);
}

int	parsing_loop(t_data *data, int *map_parse)
{
	if (!is_blank_line(data->line))
	{
		if (!*map_parse)
			*map_parse = import_params(data);
	}
	if (*map_parse == 1)
		data->map = ft_append_tab(data->map, ft_strtrim(data->line, "\n"));
	free(data->line);
	data->line = NULL;
	return (1);
}

void	check_param_not_missing(t_data *data)
{
	int	i;

	i = 0;
	while (i < NB_TEXTURES)
	{
		if (data->image->texture_path[i++] == NULL)
			exit_msg(data, "[check_param_not_missing] texture missing", -1);
	}
	if (data->image->floor_color == (unsigned int)-1)
		exit_msg(data, "[check_param_not_missing] floor_color missing", -1);
	if (data->image->ceiling_color == (unsigned int)-1)
		exit_msg(data, "[check_param_not_missing] ceiling_color missing", -1);
	if (data->map == NULL)
		exit_msg(data, "[check_param_not_missing] map is missing", -1);
}

void	import_textures(t_data *data)
{
	int			i;
	char		*fname;
	t_img_data	*t[NB_TEXTURES];

	i = 0;
	while (i < NB_TEXTURES)
	{
		data->wall_textures[i] = malloc(sizeof(t_img_data));
		i++;
	}
	i = 0;
	while (i < NB_TEXTURES)
	{
		t[i] = data->wall_textures[i];
		fname = data->image->texture_path[i];
		load_images(data, t[i], fname);
		if (!t[i]->img)
			exit_msg(data, "[import_textures] Pb loading xpm file", 1);
		i++;
	}
}

void	parse_file(char *fname, t_data *data)
{
	int		fd;
	int		map_parse;

	init_null(data, &map_parse);
	init_fd(data, &fd, fname);
	data->line = get_next_line(fd);
	if (data->line)
		while (data->line)
		{
			parsing_loop(data, &map_parse);
			if (map_parse == -1)
				break ;
			data->line = get_next_line(fd);
		}
	close(fd);
	check_param_not_missing(data);
	import_textures(data);
	if (map_parse == -1)
		exit_msg(data, "[parse_file] pb loading map", -1);
	format_map(data);
	map_parse = check_map(data);
	get_map_size(data);
	draw_map_border(data,data->map_height, data->map_width);
	data->map_size_in_units[_x] = ft_strlen(data->map[0]) * (int)UNITS_PER_BOX;
	data->map_size_in_units[_y] = ft_matrixlen(data->map) * (int)UNITS_PER_BOX;
}
