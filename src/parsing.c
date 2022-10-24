#include "cub3d.h"

int	is_blank_char(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	else
		return (0);
}

int	is_blank_line(char *line)
{
	while (*line)
	{
		if (!is_blank_char(*line++))
			return (0);
	}
	return (1);
}

unsigned int	rgb_conv(int R, int G, int B)
{
	return ((unsigned int) R * 65536 + (unsigned int) G * 256 + B);
}

int	is_map_line(char *str)
{
	if (str)
	{
		while (*str)
		{
			if (!(*str == ' ' || ft_isdigit(*str) || *str == '\n'))
				return (0);
			str++;
		}
		return (1);
	}
	else
		return (1);
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
		printf("[color[i] trimed = %s\n", color_strimed);
		if (ft_strlen(color_strimed) > 3 || !ft_strlen(color_strimed))
			wrong_color(s, color_strimed);
		colors[i] = ft_atoi(s->line_split[i]);
		printf("[color[i] = %d\n", colors[i]);
		if (colors[i] > 255 || colors[i] < 0)
			wrong_color(s, color_strimed);
		free(color_strimed);
		i++;
	}
	return (rgb_conv(colors[0], colors[1], colors[2]));
}

int	import_elemt(t_s *s)
{
	int		identifier;
	int		i;
	char *line;

	line = s->line;
	if (!line)
		return (-1);
	while (is_blank_char(*line))
		line++;
	identifier = get_identifier(s, line);
	printf("[import], s->line: %s => id: %d\n", s->line, identifier);
	if (identifier == 11)
		return (1);
	else
	{
		if (identifier == F)
			s->i->floor_color = init_f_c_color(s, line);
		else if (identifier == C)
			s->i->ceiling_color = init_f_c_color(s, line);
		else
		{
			s->line_split = ft_split(line, ' ');
			if (ft_matrixlen(s->line_split) > 3)
				error_msg("[import_elemt] WARNING: check .cub file (could be cleaner)");
			i = 1;
			while (s->line_split[i] != NULL && is_blank_line(s->line_split[i]))
				i++;
			if (s->i->texture_path[identifier])
				exit_msg(s, "param identifier must be unique", -1);
			s->i->texture_path[identifier] = ft_substr(s->line_split[i], 0, ft_strlen_char(s->line_split[i], ' '));
		}
	}
	ft_free_split(&s->line_split);
	return (0);
}

int	parsing_loop(t_s *s, int *map_parse)
{
	if (!is_blank_line(s->line) || *map_parse)
	{
		if (!*map_parse)
			*map_parse = import_elemt(s);
		if (*map_parse == 1)
			s->map = ft_append_tab(s->map, ft_strtrim(s->line, "\n"));
	}
	free(s->line);
	if (*map_parse == -1)
			return (-1);
	return (1);
}

void	set_default(t_s *s)
{
	s->i->floor_color = rgb_conv(255, 0, 0);
	s->i->ceiling_color = rgb_conv(0, 255, 0);
}

int is_available_mapcase(char c, int *is_pers)
{
	unsigned int	i;
	unsigned int	available_mapcase;
	unsigned int	nb_mapcases;
	char			*mapcases;

	available_mapcase = 0;
	mapcases = ft_strdup(MAPCASES);
	i = 0;
	nb_mapcases = ft_strlen(mapcases);
	while (i < nb_mapcases)
	{
		if (c == mapcases[i++])
		{
			available_mapcase = 1;
			break ;
		}
		if (i >= nb_mapcases - 4)
			*is_pers += 1;
	}
	free(mapcases);
	return (available_mapcase);
}

int	is_border(t_s *s, int x, int y, int matrix_len)
{
	if (s->map[y][x] == EMPTY)
		return (0);
	if (x == 0 || y == 0 || x == (int)ft_strlen(s->map[y]) - 1 || y == matrix_len - 1)
			return (1);
	else if (s->map[y - 1][x] == EMPTY || s->map[y][x - 1] == EMPTY ||s->map[y + 1][x] == EMPTY || s->map[y][x + 1] == EMPTY)
		return (1);
	else if (s->map[y - 1][x] == '\0' || s->map[y][x - 1] == '\0' ||s->map[y + 1][x] == '\0' || s->map[y][x + 1] == '\0')
		return (1);
	return (0);
}

int	check_map(t_s *s)
{
	int	x;
	int	y;
	int	matrix_len;
	int	contains_pers;

	matrix_len = ft_matrixlen(s->map);
	contains_pers = 0;
	y = 0;
	if (!s || !s->map)
		exit_msg(s, "[check_map] map is empty", -1);
	while (s->map[y])
	{
		x = 0;
		while (s->map[y][x])
		{
			if (!is_available_mapcase(s->map[y][x], &contains_pers))
				exit_msg(s, "[check_map] map contains unavailable char.", -10);
			if (is_border(s, x, y, matrix_len) && s->map[y][x] != WALL)
				exit_msg(s, "[check_map] map not surrounded by walls.", -11);
			x++;
		}
		y++;
	}
	if (contains_pers != 1)
		exit_msg(s, "[check_map] Map does not contains one hero only", -12);
	printf("[is_available_mapcase] ok\n");
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

int	parse_file(char *fname, t_s	*s)
{
	int		fd;
	int		map_parse;

	map_parse = 0;
	if (s)
		s->map = NULL;
	s->i->texture_path[NO] = NULL;
	s->i->texture_path[SO] = NULL;
	s->i->texture_path[EA] = NULL;
	s->i->texture_path[WE] = NULL;
	set_default(s);
	if (!file_extention_available(fname))
		exit_msg(s, "[parse_file] only .cub extension", -1);
	fd = open(fname, O_RDONLY);
	if (fd == -1)
	{
		error_msg("[parse_file] Error opening file (check file name)");
		return (-1);
	}
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

