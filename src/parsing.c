#include "cub3d.h"

unsigned int	rgb_conv(int R, int G, int B)
{
	return ((unsigned int) R * 65536 + (unsigned int) G * 256 + B);
}

int	conv_id_param(t_s *s, int identifier_len, char *str)
{
	int		i;
	int		ret;
	char	**identifiers;

	if (identifier_len == 2)
		identifiers = ft_split("NO ,SO ,WE ,EA ", ',');
	else if (identifier_len == 1)
		identifiers = ft_split("F ,C ", ',');
	ret = -1;
	i = 0;
	while (identifiers[i])
	{
		if (!ft_strncmp(identifiers[i], str, identifier_len + 1))
		{
			ret = i;
			break ;
		}
		i++;
	}
	ft_free_split(&identifiers);
	if (ret == -1)
		exit_msg(s, "[conv_id_param] wrong param identifier\n", -1);
	if (identifier_len == 1)
		ret += 4;
	return (ret);
}

int	get_identifier(t_s *s, char *str)
{
	int		identifier_len;

	identifier_len = ft_strlen_char(str, ' ');
	if (is_map_line(str))
		return (11);
	if (identifier_len > 2 || identifier_len < 1)
		exit_msg(s, "[get_identifier] wrong param identifier", -1);
	return (conv_id_param(s, identifier_len, str));
}

void	wrong_color(t_s *s, char *color_strimed)
{
	free(color_strimed);
	exit_msg(s, "[wrong_color]", -1);
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

void	import_param(t_s *s, int identifier, char *line)
{
	int		i;

	if (identifier == F)
		s->i->floor_color = init_f_c_color(s, line);
	else if (identifier == C)
		s->i->ceiling_color = init_f_c_color(s, line);
	else
	{
		s->line_split = ft_split(line, ' ');
		if (ft_matrixlen(s->line_split) > 3)
			error_msg("[import_params] WARNING: check .cub file (could be cleaner)");
		i = 1;
		while (s->line_split[i] != NULL && is_blank_line(s->line_split[i]))
			i++;
		if (s->i->texture_path[identifier])
			exit_msg(s, "param identifier must be unique", -1);
		s->i->texture_path[identifier] = ft_substr(s->line_split[i], 0, ft_strlen_char(s->line_split[i], ' '));
	}
}

int	import_params(t_s *s)
{
	int		identifier;
	char *line;

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

int	file_extention_available(char *fname)
{
	char *p_ext;

	if (fname)
	{
		p_ext = ft_strnstr(fname, ".cub", ft_strlen(fname));
		if (ft_strlen_char(p_ext, ' ') == 4)
			return (1);
	}
	return (0);
}

void init_null(t_s *s, int *fd, char *fname, int *map_parse)
{
	*map_parse = 0;
	if (s)
		s->map = NULL;
	s->i->texture_path[NO] = NULL;
	s->i->texture_path[SO] = NULL;
	s->i->texture_path[EA] = NULL;
	s->i->texture_path[WE] = NULL;
	s->i->floor_color = 10;
	s->i->ceiling_color = 10000;
	if (!file_extention_available(fname))
		exit_msg(s, "[parse_file] only .cub extension", -1);
	*fd = open(fname, O_RDONLY);
	if (*fd == -1)
		exit_msg(s, "[parse_file] Error opening file (check file name)", -1);
}

int	parse_file(char *fname, t_s	*s)
{
	int		fd;
	int		map_parse;

	init_null(s, &fd, fname, &map_parse);
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
	return (map_parse);
}

