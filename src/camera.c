/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suplayerko <suplayerko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:17:56 by suplayerko          #+#    #+#             */
/*   Updated: 2022/11/07 19:14:38 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
initialise le plan de la camera tel que:
	- perpendiculaire a la direction
	- le triangle forme avec le personnage fasse 66 degres
	//maybe ? - le vecteur direction coupe ce pla en sa moitie

	Le plan est defini par:
		- L'origine du plan camera
		- le vecteur a appliquer pour avoir le point suivant

	pi / 2 = 1,570796327;
*/

void	set_plane_dir(t_data *data, double plan_size)
{
	t_vector	plane_dir_unit;

	plane_dir_unit = data->player->direction;
	rotate_vector(&plane_dir_unit, (double)PI / 2.0);
	plane_dir_unit = vec_scale(plane_dir_unit, plan_size / (double)CAM_QUALITY);
	data->cam->plane_dir = plane_dir_unit;
}

void	set_plane_origin(t_data *data)
{
	t_vector	origin_plane;

	origin_plane = data->player->direction;
	rotate_vector(&origin_plane, (double)CAM_ANGLE / -2.0);
	origin_plane = vec_scale(origin_plane, ORIGIN_PLANE_SCALE);
	data->cam->origin_plane = origin_plane;
}

void	init_cam_vector(t_data *data)
{
	double		plan_size;

	plan_size = tan((double)CAM_ANGLE / 2.0) * (double)ORIGIN_PLANE_SCALE * 2.0;
	set_plane_dir(data, plan_size);
	set_plane_origin(data);
	data->cam->->direction = data->cam->origin_plane;
	data->cam->plane_size = plane_size;
}
