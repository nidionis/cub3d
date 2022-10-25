/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_colors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <ndionis@student.42mulhouse.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:17:56 by supersko          #+#    #+#             */
/*   Updated: 2022/10/25 13:39:40 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	rgb_conv(int R, int G, int B)
{
	return ((unsigned int) R * 65536 + (unsigned int) G * 256 + B);
}

unsigned int	init_f_c_color(t_s *s, char *line)
{
	int		colors[3];
	char	*color_strimed;
	int		i;

	(void)s;
	i = 0;
	line++;
	s->line_split = ft_split(line, ',');
	if (ft_matrixlen(s->line_split) != 3)
		wrong_color(s, NULL);
	while (s->line_split[i])
	{
		color_strimed = ft_strtrim(s->line_split[i], " \t");
		//printf("[color[i] trimed = %s\n", color_strimed);
		if (ft_strlen(color_strimed) > 3 || !ft_strlen(color_strimed))
			wrong_color(s, color_strimed);
		colors[i] = ft_atoi(s->line_split[i]);
		//printf("[color[i] = %d\n", colors[i]);
		if (colors[i] > 255 || colors[i] < 0)
			wrong_color(s, color_strimed);
		free(color_strimed);
		i++;
	}
	return (rgb_conv(colors[0], colors[1], colors[2]));
}
void	wrong_color(t_s *s, char *color_strimed)
{
	free(color_strimed);
	exit_msg(s, "[wrong_color]", -1);
}

