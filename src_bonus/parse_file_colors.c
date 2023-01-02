/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_colors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:17:56 by supersko          #+#    #+#             */
/*   Updated: 2023/01/02 12:57:01 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub3d_bonus.h"

unsigned int	rgb_conv(int R, int G, int B)
{
	return ((unsigned int) R * 65536 + (unsigned int) G * 256 + B);
}

/* convert lines containing ceiling and floor color to the value */
unsigned int	init_f_c_color(t_data *data, char *line)
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
		color_strimed = ft_strtrim(data->line_split[i], " \t\n");
		if (ft_strlen(color_strimed) > 3 || !ft_strlen(color_strimed))
			wrong_color(data, color_strimed);
		colors[i] = ft_atoi(color_strimed);
		if (colors[i] > 255 || colors[i] < 0)
			wrong_color(data, color_strimed);
		free(color_strimed);
		i++;
	}
	return (rgb_conv(colors[0], colors[1], colors[2]));
}

void	wrong_color(t_data *data, char *color_strimed)
{
	free(color_strimed);
	exit_msg(data, "[wrong_color]", -1);
}
