/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_import.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:17:56 by supersko          #+#    #+#             */
/*   Updated: 2023/01/04 16:36:25 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub3d_bonus.h"

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
	draw_map_border(data, data->map_height, data->map_width);
	data->map_size_in_units[_x] = ft_strlen(data->map[0]) * (int)UNITS_PER_BOX;
	data->map_size_in_units[_y] = ft_matrixlen(data->map) * (int)UNITS_PER_BOX;
}
