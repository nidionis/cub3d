/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <ndionis@student.42mulhouse.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:17:56 by supersko          #+#    #+#             */
/*   Updated: 2022/10/25 17:39:44 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	import_texture_path(t_s *s, int identifier, char *line)
{
	int	i;

	s->line_split = ft_split(line, ' ');
	if (ft_matrixlen(s->line_split) > 3)
		error_msg("[import_params] WARNING: \
				check .cub file (could be cleaner)");
	i = 1;
	while (s->line_split[i] != NULL && is_blank_line(s->line_split[i]))
		i++;
	if (s->i->texture_path[identifier])
		exit_msg(s, "param identifier must be unique", -1);
	s->i->texture_path[identifier] = \
	ft_substr(s->line_split[i], 0, ft_strlen_char(s->line_split[i], ' '));
}

void	import_param(t_s *s, int identifier, char *line)
{
	if (identifier == F)
		s->i->floor_color = init_f_c_color(s, line);
	else if (identifier == C)
		s->i->ceiling_color = init_f_c_color(s, line);
	else
		import_texture_path(s, identifier, line);
}

int	import_params(t_s *s)
{
	int		identifier;
	char	*line;

	line = s->line;
	if (!line)
		return (-1);
	while (is_blank_char(*line))
		line++;
	identifier = get_identifier(s, line);
	//printf("[import], s->line: %s => id: %d\n", s->line, identifier);
	if (identifier == 11) // copying map matrix
		return (1);
	else
		import_param(s, identifier, line);
	ft_free_split(&s->line_split);
	return (0);
}

int	parsing_loop(t_s *s, int *map_parse)
{
	if (!is_blank_line(s->line) || *map_parse)
	{
		if (!*map_parse)
			*map_parse = import_params(s);
		if (*map_parse == 1)
			s->map = ft_append_tab(s->map, ft_strtrim(s->line, "\n"));
	}
	free(s->line);
	return (1);
}

void	init_null(t_s *s, int *map_parse)
{
	int	i;

	*map_parse = 0;
	if (s)
		s->map = NULL;
	i = 0;
	while (i < NB_TEXTURES)
		s->i->texture_path[i++] = NULL;
	s->i->floor_color = 10;
	s->i->ceiling_color = 10000;
}

void	init_fd(t_s *s, int *fd, char *fname)
{
	file_extention_available(s, fname);
	*fd = open(fname, O_RDONLY);
	if (*fd == -1)
		exit_msg(s, "[init_fd] Error opening file (check file name)", -1);
}

void	parse_file(char *fname, t_s	*s)
{
	int		fd;
	int		map_parse;

	init_null(s, &map_parse);
	init_fd(s, &fd, fname);
	s->line = get_next_line(fd);
	if (s->line)
	{
		while (s->line)
		{
			parsing_loop(s, &map_parse);
			if (map_parse == -1)
				break ;
			s->line = get_next_line(fd);
		}
	}
	close(fd);
	if (map_parse != -1)
		map_parse = check_map(s);
	if (map_parse == -1)
		exit_msg(s, "[parse_file] pb loading map", -1);
}
