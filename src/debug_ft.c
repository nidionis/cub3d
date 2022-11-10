/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_ft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suplayerko <suplayerko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:17:56 by suplayerko          #+#    #+#             */
/*   Updated: 2022/10/26 17:47:02 by suplayerko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_player(t_data *data, int fd)
{
	if (fd < 0)
		error_msg("[print_player] warning: wrong fd]");
	dprintf(fd, "[Pers]	pos_map: 	[%5d,%5d]\n", data->player->pos_map.x, data->player->pos_map.y);
	dprintf(fd, "[Pers]	pos_box: 	[%5d,%5d]\n", data->player->pos_box.x, data->player->pos_box.y);
	dprintf(fd, "[Pers]	direction:	[%5f,%5f]\n", data->player->direction.x, data->player->direction.y);
	dprintf(fd, "[Pers]	pos_in_pix:	[%5d,%5d]\n", data->player->pos_in_pix.x, data->player->pos_in_pix.y);
	dprintf(fd, "[Pers]	pos_in_step:	[%5d,%5d]\n", data->player->pos_in_step.x, data->player->pos_in_step.y);
}

void	print_cam(t_data *data, int fd)
{
	if (fd < 0)
		error_msg("[print_params] warning: wrong fd]");
	dprintf(fd, "[cam]	origin_plane:	[%lf, %lf]\n", data->cam->origin_plane.x, data->cam->origin_plane.y);
	dprintf(fd, "[cam]	plane_dir:[%lf, %lf]\n", data->cam->plane_dir.x, data->cam->plane_dir.y);
}

void	print_params(t_data *data, int fd)
{
	if (fd < 0)
		error_msg("[print_params] warning: wrong fd]");
	dprintf(fd, "[img]	ceili_col:	[%d]\n", data->image->ceiling_color);
	dprintf(fd, "[img]	floor_color:[%d]\n", data->image->floor_color);
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
	print_player(data, fd);
	print_params(data, fd);
	print_map(data, fd);
}

void	redir_debug_file_msg(char *fname, char *msg)
{
	int fd = open(fname, O_WRONLY | O_APPEND | O_CREAT, 0000666);
	if (fd < 0)
		error_msg("[redir_debug] warning: cannot open file]");
	dprintf(fd, "[message] %s\n", msg);
	close(fd);

}

void	redir_debug_file_logs(t_data *data, char *fname, int log_type)
{
	int fd = open(fname, O_WRONLY | O_APPEND | O_CREAT, 0000666);
	if (fd < 0)
		error_msg("[redir_debug] warning: cannot open file]");
	if (log_type == DATA)
		print_data(data, fd);
	if (log_type == PARAM)
		print_params(data, fd);
	if (log_type == PLAYER)
		print_player(data, fd);
	if (log_type == MAP)
		print_map(data, fd);
	if (log_type == CAM)
		print_cam(data, fd);
	dprintf(fd, "\t====================================\n");
	close(fd);

}

void	draw_wall_line(t_data *data, int i)
{
	t_point	start;
	t_point	end;
	t_ray	ray;
	int		line_height;
	int		color;
	int		line_width = SCREEN_WIDTH / CAM_QUALITY;
	int		loop;
	double	good_ratio;
	
	ray = data->cam->arRay[i];
	good_ratio = (double)SCREEN_HEIGHT * (double)UNITS_PER_BOX;
	start.x = i * line_width;
	end.x = i * line_width;
	line_height = good_ratio / ray.len;
	if (line_height > SCREEN_HEIGHT)
		line_height = (int)SCREEN_HEIGHT;
	start.y = (int)SCREEN_HEIGHT / 2 - line_height / 2;
	end.y = (int)SCREEN_HEIGHT / 2 + line_height / 2;

	if (ray.side == NORTH)
		color = rgb_conv(0, 0, 255);
	else if (ray.side == SOUTH)
		color = rgb_conv(255, 255, 255);
	else if (ray.side == EAST)
		color = rgb_conv(0, 255, 0);
	else if (ray.side == WEST)
		color = rgb_conv(255, 0, 0);
	else
		color = rgb_conv(20, 20, 20);
	loop = 0;
	while (loop < line_width)
	{
		draw_line(data, &start, &end, color);
		start.x++;
		end.x++;
		loop++;
	}
	
}

