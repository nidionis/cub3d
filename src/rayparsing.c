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
	t_ray 	*ray;
	t_cam	*cam;
	
	cam = data->cam;
	ray = cam->beam;
	ray->direction_len = vec_len(ray->direction);
	ray->delta_distances.x = ray->direction_len / ray->direction.x;
	ray->delta_distances.y = ray->direction_len / ray->direction.y;
	ray->vector_deltaX = vec_scale(ray->direction, ray->delta_distances.x / ray->direction_len);
	ray->vector_deltaY = vec_scale(ray->direction, ray->delta_distances.y / ray->direction_len);
}

/*
  not sure of the calcul, but set the distance to the next_case 
 	delta_dist MUST BE UPDATED
	*/
void	set_side_distance(t_data *data)
{
	t_cam		*cam;
	t_ray		*ray;
	t_player	*player;
	
	cam = data->cam;
	ray = cam->beam;
	player = data->player;
	ray->side_distances.x = ray->delta_distances.x * (double)(UNITS_PER_BOX - player->pos_box.x) / (double)UNITS_PER_BOX;
	ray->side_distances.y = ray->delta_distances.y * (double)(UNITS_PER_BOX - player->pos_box.y) / (double)UNITS_PER_BOX;
	ray->vector_sideX = vec_scale(ray->direction, ray->side_distances.x / ray->direction_len);
	ray->vector_sideY = vec_scale(ray->direction, ray->side_distances.y / ray->direction_len);
}

void	set_beam(t_data *data, t_point ray_position[2])
{
	ray_position[_x] = data->player->pos_in_pix;
	ray_position[_y] = data->player->pos_in_pix;
	set_delta_distance(data);
	set_side_distance(data);
}

int	first_step(t_data *data, t_point ray_position[2], double len[2])
{
	t_ray	*ray;

	ray = data->cam->beam;
	len[_x] = ray->side_distances.x;
	len[_y] = ray->side_distances.y;
	translate_pt(ray->vector_sideX, &ray_position[_x]);
	if (pix_pos_to_map_case(ray_position[_x], data->map) == WALL)
		return (_x);
	translate_pt(ray->vector_sideY, &ray_position[_y]);
	if (pix_pos_to_map_case(ray_position[_y], data->map) == WALL)
		return (_y);
	return (-1);
}

int	beam_step(t_data *data, t_point ray_position[2], double len[2])
{
	t_ray	*ray;

	ray = data->cam->beam;
	if (len[_x] < len[_y])
	{
		translate_pt(ray->vector_deltaX, &ray_position[_x]);
		len[_x] += ray->delta_distances.x;
		if (pix_pos_to_map_case(ray_position[_x], data->map) == WALL)
			return (_x);
	}
	else
	{
		translate_pt(ray->vector_deltaY, &ray_position[_y]);
		len[_y] += ray->delta_distances.y;
		if (pix_pos_to_map_case(ray_position[_y], data->map) == WALL)
			return (_y);
	}
	return (-1);
}

void	raysult(t_data *data, t_point ray_position[2], double len[2], int side_hit)
{
	t_cam		*cam;
	t_ray		*ray;
	t_vector	cam_dir;

	cam = data->cam;
	ray = cam->beam;
	ray->len = len[side_hit];
	if (side_hit == _x)
	{
		if (ray->direction.y > 0)
			ray->side = NORTH;
		else
			ray->side = SOUTH;
	}
	else
	{
		if (ray->direction.x < 0)
			ray->side = EAST;
		else
			ray->side = WEST;
	}
	ray->hit_point = ray_position[side_hit];
	cam_dir = data->cam->plane_dir;
	ray->dist_from_plan = vectors_angle_sin(ray->direction, cam_dir) * ray->len;
}

/*
	return absulute point (in UNIT_PER_BOX) hitting the wall
	delta_distance must be set before side distance
*/
t_ray	beam(t_data *data)
{
	t_point		ray_position[2]; // x and y
	double		len[2];
	t_cam		*cam;
	int			wall_hit;

	cam = data->cam;
	set_beam(data, ray_position);
	wall_hit = first_step(data, ray_position, len);
	while (wall_hit == -1)
	{
		if (ray_position[0].x < 0 || ray_position[0].y < 0 || ray_position[1].x < 0 || ray_position[1].y < 0)
		{
			fprintf(stderr, "[beam] ray overflow\n");
			break;
		}
		wall_hit = beam_step(data, ray_position, len);
	}
	raysult(data, ray_position, len, wall_hit);
	return (*(cam->beam));
}

void	set_arRay(t_data *data)
{
	t_ray	*ray;
	t_cam	*cam;
	int		i_ray;

	init_cam_vector(data);
	cam = data->cam;
	ray = cam->beam;
	i_ray = 0;
	while (i_ray < CAM_QUALITY)
	{
		cam->arRay[i_ray] = beam(data);
		translate_vector_as_pt(cam->plane_dir, &ray->direction);
		i_ray++;
	}
}
