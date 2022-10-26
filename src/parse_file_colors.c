/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_colors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:17:56 by supersko          #+#    #+#             */
/*   Updated: 2022/10/26 15:47:21 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	rgb_conv(int R, int G, int B)
{
	return ((unsigned int) R * 65536 + (unsigned int) G * 256 + B);
}

unsigned int	init_f_c_color( t_data *data, char *line)
{
	int		colors[3];
	char	*color_strimed;
	int		i;

	(void) data;
	i = 0;
	line++;
	data->line_split = ft_split(line, ',');
	if (ft_matrixlen(data->line_split) != 3)
		wrong_color(data, NULL);
	while (data->line_split[i])
	{
		color_strimed = ft_strtrim(data->line_split[i], " \t");
		//printf("[color[i] trimed = %s\n", color_strimed);
		if (ft_strlen(color_strimed) > 3 || !ft_strlen(color_strimed))
			wrong_color(data, color_strimed);
		colors[i] = ft_atoi(data->line_split[i]);
		//printf("[color[i] = %d\n", colors[i]);
		if (colors[i] > 255 || colors[i] < 0)
			wrong_color(data, color_strimed);
		free(color_strimed);
		i++;
	}
	return (rgb_conv(colors[0], colors[1], colors[2]));
}
void	wrong_color( t_data *data, char *color_strimed)
{
	free(color_strimed);
	exit_msg(data, "[wrong_color]", -1);
}

