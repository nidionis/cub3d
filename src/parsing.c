#include "cub3d.h"

int	is_blank_char(char c)
{
	if (c == ' ' || c == '\t')
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

int	get_identifier(char *str)
{
	char	**identifiers;
	int		identifier_len;
	int		ret;
	int		i;

	ret = -1;
	identifier_len = ft_strlen_char(str, ' ');
	if (is_map_line(str))
		return (11);
	if (identifier_len > 2 || identifier_len < 1)
		return (-1);
	else if (identifier_len == 2)
		identifiers = ft_split("NO ,SE ,WE ,EA ", ',');
	else if (identifier_len == 1)
		identifiers = ft_split("F,C", ',');
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
	if (ret != -1 && identifier_len == 1)
		ret += 4;
	return (ret);
}

void	wrong_color(char *color_strimed, char ***line_splitted)
{
	error_msg("[init_f_c_color] wrong color");
	free(color_strimed);
	ft_free_split(line_splitted);
}

int	init_f_c_color(t_s *s, char *line)
{
	char	**line_splitted;
	int		colors[3];
	char	*color_strimed;
	int		i;
	(void)s;

	line++;
	i = 0;
	line_splitted = ft_split(line, ',');
	while (line_splitted[i])
	{
		color_strimed = ft_strtrim(line_splitted[i], " \t");
		if (ft_strlen(color_strimed) > 3)
		{
			wrong_color(color_strimed, &line_splitted);
			return (-1);
		}
		colors[i] = ft_atoi(line_splitted[i]);
		if (colors[i] > 255 && colors[i] < 0)
		{
			wrong_color(color_strimed, &line_splitted);
			return (-1);
		}
		if (i > 3)
		{
			wrong_color(color_strimed, &line_splitted);
			return (-1);
		}
		free(color_strimed);
		i++;
	}
	ft_free_split(&line_splitted);
	return (1);
}

int	import_elemt(t_s *s, char *line)
{
	int		identifier;
	char	**line_splitted;
	int		i;

	if (!line)
		return (-1);
	while (is_blank_char(*line))
		line++;
	identifier = get_identifier(line);
	if (identifier == -1)
	{
		error_msg("[import_elemt] wrong identifier");
		return (-1);
	}
	else if (identifier == 11)
		return (1);
	else
	{
		if (identifier == F || identifier == C)
		{
			if (init_f_c_color(s, line) == -1)
				return (-1);
		}
		else
		{
			line_splitted = ft_split(line, ' ');
			if (ft_matrixlen(line_splitted) > 3)
				error_msg("[import_elemt] WARNING: check .cub file");
			i = 1;
			while (line_splitted[i] != NULL && !ft_strncmp(line_splitted[i], "", 1))
				i++;
			s->i->texture_path[identifier] = ft_substr(line_splitted[i], 0, ft_strlen_char(line_splitted[i], ' '));
		}
	}
	return (0);
}

int	parsing_loop(char *line, t_s *s, int *map_parse)
{
	if (!is_blank_line(line))
	{
		if (!*map_parse)
			*map_parse = import_elemt(s, line);
		if (*map_parse == 1)
			s->map = ft_append_tab(s->map, ft_strtrim(line, "\n"));
	}
	free(line);
	if (*map_parse == -1)
			return (-1);
	return (1);
}

void	set_default(t_s *s)
{
	s->i->floor_color = rgb_conv(255, 0, 0);
	s->i->ceiling_color = rgb_conv(0, 255, 0);
}

static int is_available_mapcase(char c)
{
	if (!(c == WALL || c == FLOOR || c == EMPTY))
	{
		fprintf(stderr, "%c\n", c);
		error_msg("[is_available_mapcase] map contains unavailable case.");
		return (1);
	}
	return (0);
}

static int	is_border(t_s *s, int x, int y, int matrix_len)
{
	if (s->map[y][x] == EMPTY)
		return (0);
	if (x == 0 || y == 0 || x == (int)ft_strlen(s->map[y]) - 1 || y == matrix_len - 1)
			return (1);
	else if (s->map[y - 1][x] == EMPTY || s->map[y][x - 1] == EMPTY ||s->map[y + 1][x] == EMPTY || s->map[y][x + 1] == EMPTY)
		return (1);
	return (0);
}

int	check_map(t_s *s)
{
	int	x;
	int	y;
	int	matrix_len;

	matrix_len = ft_matrixlen(s->map);
	y = 0;
	if (!s || !s->map)
		return (-1);
	while (s->map[y])
	{
		x = 0;
		while (s->map[y][x])
		{
			if (!is_available_mapcase(s->map[y][x]))
				return (-1);
			if (is_border(s, x, y, matrix_len) && s->map[y][x] != WALL)
			{
				error_msg("[check_map] map not surrounded by walls.");
				return (-1);
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	parse_file(char *fname, t_s	*s)
{
	int		fd;
	int		map_parse;
	char	*line;

	map_parse = 0;
	if (s)
		s->map = NULL;
	//set_default(s);
	fd = open(fname, O_RDONLY);
	if (fd == -1)
	{
		error_msg("[parse_file] Error opening file (check file name)");
		return (-1);
	}
	line = get_next_line(fd);
	printf("[parse_file] line: %s\n", line);
	if (line)
	{
		while (line)
		{
			parsing_loop(line, s, &map_parse);
			if (map_parse == -1)
				break ;
			line = get_next_line(fd);
		}
	}
	close(fd);
	if (map_parse != -1)
		map_parse = check_map(s);
	return (map_parse);
}

