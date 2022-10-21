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

int	import_elemt(t_s *s, char *line)
{
	while (line
}

int	parsing_loop(char *line, t_s *s, int *map_parse)
{
	if (!is_blank_line(line))
	{
		if (!*map_parse)
			*map_parse = import_elemt(s, line);
		if (*map_parse == 1)
			s->map = ft_append_tab(s->map);
	}
	if (map_parse != 1)
		free(line);
	if (*map_parse == -1)
			return (-1);
	return (1);
}

void	set_default(t_s *s)
{
	s->floor_color = rgb_conv(255, 0, 0);
	s->ceiling_color = rgb_conv(0, 255, 0);
}

static int is_available_mapcase(char c)
{
	if (s->map[x][y] == FLOOR || s->map[x][y] == WALL || s->map[x][y] == EMPTY)
		return (1);
	error_msg("[is_available_mapcase] map contains unavailable case.");
	return (0);
}

static int	is_border(t_s *s, int x, int y, int matrix_len)
{
	if (s->map[y][x] == EMPTY)
		return (0);
	if (x == 0 || y == 0 || x == ft_strlen(s->map[y]) - 1 || y == matrix_len - 1)
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

	matrix_len = ft_matrixlen(s);
	y = 0;
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
			y++;
		}
		x++;
	}
	return (1);
}

int	parse_file(char *fname, t_s	*s)
{
	int		fd;
	int		map_parse;
	char	*line;

	fd = open(fname, O_RDONLY);
	if (fd == -1)
	{
		error_msg("[parse_file] Error opening file (check file name)");
		return (-1);
	}
	map_parse = 0;
	set_default(s);
	line = get_next_line(fd);
	while (line)
	{
		parsing_loop(line, s, &map_parse);
		if (map_parse == -1)
			break ;
		line = get_next_line(fd);
	}
	close(fd);
	if (map_parse != -1)
		map_parse = check_map(s);
	return (map_parse);
}
