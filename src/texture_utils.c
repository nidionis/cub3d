#include <cub3d.h>

int	grep_width(char *line)
{
	while (!ft_isdigit(*line))
		line++;
	return (ft_atoi(line));
}

int	grep_height(char *line)
{
	while (!ft_isdigit(*line))
		line++;
	while (ft_isdigit(*line))
		line++;
	while (!ft_isdigit(*line))
		line++;
	return (ft_atoi(line));
}

void	set_texture_size(t_texture *texture)
{
	int	fd;
	char	*line;

	fd = open(texture->path, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
	       	if (!ft_strchr(line, '"'))
		{
			free(line);
			line = get_next_line(fd);
		}
		else
		{
			texture->size[_x] = grep_width(line);
			texture->size[_y] = grep_height(line);
			return ;
		}
	}
	//if (!texture->size[0] || !texture->size[1])
	//	exit_msg(data, "[set_texture_size] problem to grep picture size", 1);
}

