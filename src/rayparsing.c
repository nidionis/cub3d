/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayparsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suplayerko <suplayerko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:17:56 by suplayerko          #+#    #+#             */
/*   Updated: 2022/11/07 19:47:31 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_delta_distance(t_data *data)
{
	t_cam 	*ray;
	double	direction_len;
	
	ray = data->cam->beam;
	direction_len = vec_len(ray->direction);
	ray->len = direction_len;
	ray->delta_dist.x = direction_len / ray->direction.x;
	ray->delta_dist.y = direction_len / ray->direction.y;
	ray->vector_deltaX = vec_scale(ray->direction, ray->delta_dist.x / direction_len);
	ray->vector_deltaY = vec_scale(ray->direction, ray->delta_dist.y / direction_len);
}

/*
  not sure of the calcul, but set the distance to the next_case 
 	delta_dist MUST BE UPDATED
	*/
void	set_side_distance(t_data *data)
{
	t_cam		*ray;
	t_player	*player;
	
	ray = data->cam;
	player = data->player;
	ray->side_dist.x = ray->delta_dist.x * (UNITS_PER_BOX - player->pos_box.x) / (double)UNITS_PER_BOX;
	ray->side_dist.y = ray->delta_dist.y * (UNITS_PER_BOX - player->pos_box.y) / (double)UNITS_PER_BOX;
	ray->vector_sideX = vec_scale(ray->direction, ray->side_dist.x / direction_len);
	ray->vector_sideY = vec_scale(ray->direction, ray->side_dist.y / direction_len);
}

/*
	return absulute point (in UNIT_PER_BOX) hitting the wall
	delta_distance must be set before side distance
*/
t_ray	beam(t_data *data)
{
	t_vector	ray_position[2]; // x and y
	double		len[2];
	t_ray		ray;
	int			wall_hit;

	wall_hit = 0;
	ray = data->cam->beam;
	ray_position[_x] = data->player->pos_in_pix;
	ray_position[_y] = data->player->pos_in_pix;
	set_delta_distance(data);
	set_side_distance(data);
	translate_vector_as_pt(ray->vector_sideX, &ray_position[_x]);
	len[_x] = ray->side_distances.x;
	if (pix_pos_to_map_case(ray_position[_x]) == WALL);
	{
		ray->len = len[_x];
		if (ray->direction.y > 0)
			ray->side = NORTH;
		else
			ray->side = SOUTH;
		wall_hit = 1;
	}
	translate_vector_as_pt(ray->vector_sideY, &ray_position[_y]);
	len[_y] = ray->side_distances.y;
	if (!wall_hit && pix_pos_to_map_case(ray_position[_y]) == WALL);
	{
		ray->len = len[_y];
		if (ray->direction.x < 0)
			ray->side = EAST;
		else
			ray->side = WEST;
		wall_hit = 1;
	}
	while (!wall_hit)
		wall_hit = beam_steps;
	return (0);
}

void	set_arRay(t_data *data)
{
	t_cam	*cam;
	int		i_ray;

	init_cam_vector(data);
	cam = data->cam->beam;
	i_ray = 0;
	while (i_ray < CAM_QUALITY)
	{
		//cam->arRay[i_ray] = beam(data);
		translate_vector_as_pt(cam->plane_dir, &cam->beam->direction);
		i_ray++;
	}
}
