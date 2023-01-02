/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_ft.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:17:56 by suplayerko        #+#    #+#             */
/*   Updated: 2022/12/30 15:41:53 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	set_plane_dir(t_data *data, double plane_size)
{
	t_vector	plane_dir_unit;
	double		scale;
	double		nonante_deg;
	double		cam_quality;

	cam_quality = (double)get_res_width();
	scale = plane_size / cam_quality;
	nonante_deg = (double)PI;
	nonante_deg /= (double)2.0;
	plane_dir_unit = data->player->direction;
	plane_dir_unit = vec_scale(plane_dir_unit, scale);
	rotate_vector(&plane_dir_unit, nonante_deg);
	data->cam->plane_dir = plane_dir_unit;
}

/* set the point giving the direction for the first ray */
void	set_plane_origin(t_data *data)
{
	t_vector	origin_plane;

	origin_plane = vec_scale(data->player->direction, \
		(double)ORIGIN_PLANE_SCALE);
	rotate_vector(&origin_plane, (double)CAM_ANGLE / (double)-2.0);
	data->cam->origin_plane = origin_plane;
}

/* set the vector to apply to "origin plane" for the next mesurement */
void	init_cam_vector(t_data *data)
{
	double		plane_size;

	plane_size = tan((double)CAM_ANGLE / \
		(double)2.0) * (double)ORIGIN_PLANE_SCALE * (double)2.0;
	set_plane_origin(data);
	set_plane_dir(data, plane_size);
	data->cam->beam->direction = data->cam->origin_plane;
	data->cam->plane_size = plane_size;
}
