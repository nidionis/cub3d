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

void	set_beam(data)
{
	set_delta_distance(data);
	set_side_distance(data);
}

/*
	return absulute point (in UNIT_PER_BOX) hitting the wall
*/
t_vector	beam(t_data *data)
{
	t_vector	hit_point;
	double		distance;

	return (0);
}

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
