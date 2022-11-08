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

void	set_plane_dir(t_data *data, double plane_size)
{
	t_vector	plane_dir_unit;

	plane_dir_unit = data->player->direction;
	rotate_vector(&plane_dir_unit, (double)PI / 2.0);
	plane_dir_unit = vec_scale(plane_dir_unit, plane_size / (double)CAM_QUALITY);
	data->cam->plane_dir = plane_dir_unit;
}

void	set_delta_distance(t_data *data)
{
	t_ray 	ray;
	t_cam	*cam;
	
	cam = data->cam;
	cam->beam.direction_len = vec_len(ray.direction);
	ray = cam->beam;
	cam->beam.delta_distances.x = ray.direction_len / ray.direction.x;
	cam->beam.delta_distances.y = ray.direction_len / ray.direction.y;
	cam->beam.vector_deltaX = vec_scale(ray.direction, ray.delta_distances.x / ray.direction_len);
	cam->beam.vector_deltaY = vec_scale(ray.direction, ray.delta_distances.y / ray.direction_len);
}

/*
  not sure of the calcul, but set the distance to the next_case 
 	delta_dist MUST BE UPDATED
	*/
void	set_side_distance(t_data *data)
{
	t_cam		*cam;
	t_ray		ray;
	t_player	*player;
	
	cam = data->cam;
	ray = cam->beam;
	player = data->player;
	cam->beam.side_distances.x = ray.delta_distances.x * (UNITS_PER_BOX - player->pos_box.x) / (double)UNITS_PER_BOX;
	cam->beam.side_distances.y = ray.delta_distances.y * (UNITS_PER_BOX - player->pos_box.y) / (double)UNITS_PER_BOX;
	cam->beam.vector_sideX = vec_scale(ray.direction, ray.side_distances.x / ray.direction_len);
	cam->beam.vector_sideY = vec_scale(ray.direction, ray.side_distances.y / ray.direction_len);
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
	double		plane_size;

	plane_size = tan((double)CAM_ANGLE / 2.0) * (double)ORIGIN_PLANE_SCALE * 2.0;
	set_plane_origin(data);
	set_plane_dir(data, plane_size);
	data->cam->beam.direction = data->cam->origin_plane;
	data->cam->plane_size = plane_size;
}
