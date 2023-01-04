/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_menu_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 11:15:30 by dpaulino          #+#    #+#             */
/*   Updated: 2023/01/04 17:43:25 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	*remove_char(char *str, char c)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = malloc(sizeof(char) * 30);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			tmp[j] = str[i];
			j++;
		}
		i++;
	}
	tmp[j] = '\0';
	return (tmp);
}

void	verify_fd(int fd, char *path)
{
	if (fd == -1)
	{
		printf("%s <-- File does not exit\n", path);
		exit(0);
	}
}

t_point	get_img_size(char *path)
{
	int		fd;
	char	*buffer;
	char	*buffer2;
	char	**tmp;
	t_point	size;

	fd = open(path, O_RDWR);
	verify_fd(fd, path);
	buffer = get_next_line(fd);
	while (ft_strncmp(buffer, "\"", 1))
	{
		free(buffer);
		buffer = get_next_line(fd);
	}
	buffer2 = remove_char(buffer, '\"');
	free(buffer);
	buffer = remove_char(buffer2, ',');
	free(buffer2);
	tmp = ft_split(buffer, ' ');
	close(fd);
	size.x = atoi(tmp[0]);
	size.y = atoi(tmp[1]);
	ft_free_split(&tmp);
	free(buffer);
	return (size);
}
