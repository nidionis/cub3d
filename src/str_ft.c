#include <cub3d.h>

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
