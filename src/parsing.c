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

int	parse_file(char *fname, t_s	*s)
{
	int		fd;
	int		map_parse;
	char	*line;

	fd = open(fname, O_RDONLY);
	map_parse = 0;
	set_default(s);
	line = get_next_line(fd);
	while (line)
	{
		parsing_loop(line, s, &map_parse);
		line = get_next_line(fd);
	}
	close(fd);
}
