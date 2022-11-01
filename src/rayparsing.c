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
	- le triangle dorme avec le personnage fasse 66 degres
	- le vecteur direction coupe ce pla en sa moitie

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
	origin_plane = vec_scale(origin_plane, 0.5);
	data->cam->origin_plane = origin_plane;
}

void	set_delta_distance(t_data *data)
{
	t_cam *cam;
	
	cam = data->cam;
	cam->delta_dist.x = 1.0 / cam->ray_direction.x;
	cam->delta_dist.y = 1.0 / cam->ray_direction.y;
}

/* not sure of the calcul, but set the distance to the next_case */
void	set_side_distance(t_data *data)
{
	t_cam *cam;
	t_player *player;
	
	cam = data->cam;
	player = data->player;
	cam->side_dist.x = cam->delta_dist.x * (UNITS_PER_BOX - player->pos_box.x) / (double)UNITS_PER_BOX;
	cam->side_dist.y = cam->delta_dist.y * (UNITS_PER_BOX - player->pos_box.y) / (double)UNITS_PER_BOX;
}

void	init_cam_vector(t_data *data)
{
	double		plan_size;

	plan_size = tan((double)CAM_ANGLE / 2.0);
	set_plane_dir(data, plan_size);
	set_plane_origin(data);
	data->cam->ray_direction = data->cam->origin_plane;
}

/* return absulute point (in UNIT_PER_BOX) hitting the wall
t_vector	beam(t_data *data)
{
	return (0);
}
*/

void	set_arRay(t_data *data)
{
	t_cam	*cam;
	int		i_ray;

	init_cam_vector(data);
	cam = data->cam;
	i_ray = 0;
	while (i_ray < CAM_QUALITY)
	{
		//cam->arRay[i_ray] = beam(data);
		translate_vector_as_pt(cam->plane_dir, &cam->ray_direction);

		i_ray++;
	}
}
