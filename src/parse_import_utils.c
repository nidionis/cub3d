/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_import_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 16:32:21 by dpaulino          #+#    #+#             */
/*   Updated: 2023/01/04 17:44:27 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
