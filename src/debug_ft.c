/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_ft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:17:56 by supersko          #+#    #+#             */
/*   Updated: 2022/10/26 16:24:32 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_pers(t_data *data, int fd)
{
	if (fd < 0)
		error_msg("[print_pers] warning: wrong fd]");
	dprintf(fd, "[Pers]	pos_map: [%5d,%5d]\n", data->player->pos_map.x, data->player->pos_map.y);
	dprintf(fd, "[Pers]	pos_box: [%5d,%5d]\n", data->player->pos_box.x, data->player->pos_box.y);
	dprintf(fd, "[Pers]	dir: 	 [%5d,%5d]\n", data->player->dir.x, data->player->dir.y);
	dprintf(fd, "[Pers]	plane: 	 [%5d,%5d]\n", data->player->plane.x, data->player->plane.y);
}

void	print_params(t_data *data, int fd)
{
	if (fd < 0)
		error_msg("[print_params] warning: wrong fd]");
	dprintf(fd, "[img]	ceiling_color: [%d]\n", data->image->ceiling_color);
	dprintf(fd, "[img]	floor_color: [%d]\n", data->image->floor_color);
	dprintf(fd, "[img]	texture NO: [%s]\n", data->image->texture_path[NO]);
	dprintf(fd, "[img]	texture SO: [%s]\n", data->image->texture_path[SO]);
	dprintf(fd, "[img]	texture EA: [%s]\n", data->image->texture_path[EA]);
	dprintf(fd, "[img]	texture WE: [%s]\n", data->image->texture_path[WE]);
}


void	print_map(t_data *data, int fd)
{
	char	**map = data->map;
	if (fd < 0)
		error_msg("[print_map] warning: wrong fd]");
	while (*map)
		dprintf(fd, "%s\n", *map++);
}

void	print_data(t_data *data, int fd)
{
	if (fd < 0)
		error_msg("[print_data] warning: wrong fd]");
	print_pers(data, fd);
	print_params(data, fd);
	print_map(data, fd);
}

void	redir_debug_file_logs(t_data *data, char *fname)
{
	int fd = open(fname, O_RDWR | O_APPEND);
	if (fd < 0)
		error_msg("[redir_debug] warning: cannot open file]");
	print_data(data, fd);
	close(fd);
}