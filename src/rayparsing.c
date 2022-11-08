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

void	set_beam(t_data *data, t_point (*ray_position)[2], double (*len)[2])
{
	(*ray_position)[_x] = data->player->pos_in_pix;
	(*ray_position)[_y] = data->player->pos_in_pix;
	set_delta_distance(data);
	set_side_distance(data);
}

int	first_step(t_data *data, t_point (*ray_position)[2], double (*len)[2])
{
	t_ray	ray;

	ray = data->cam->beam;
	(*len)[_x] = data->cam->beam.side_distances.x;
	(*len)[_y] = data->cam->beam.side_distances.y;
	translate_pt(ray.vector_sideX, ray_position[_x]);
	if (pix_pos_to_map_case((*ray_position)[_x], data->map) == WALL)
		return (_x);
	translate_pt(ray.vector_sideY, ray_position[_y]);
	if (pix_pos_to_map_case((*ray_position)[_y], data->map) == WALL)
		return (_y);
	return (-1);
}

int	beam_step(t_data *data, t_point (*ray_position)[2], double (*len)[2])
{
	t_ray	ray;

	ray = data->cam->beam;
	if ((*len)[_x] < (*len)[_y])
	{
		translate_pt(ray.vector_deltaX, ray_position[_x]);
		(*len)[_x] += ray.delta_distances.x;
		if (pix_pos_to_map_case((*ray_position)[_x], data->map) == WALL)
			return (_x);
	}
	else
	{
		translate_pt(ray.vector_deltaY, ray_position[_y]);
		(*len)[_y] += ray.delta_distances.y;
		if (pix_pos_to_map_case((*ray_position)[_y], data->map) == WALL)
			return (_y);
	}
	return (-1);
}

void	raysult(t_data *data, t_point ray_position[2], double len[2], int side_hit)
{
	t_cam		*cam;
	t_ray		ray;
	t_vector	player_dir;

	cam = data->cam;
	ray = cam->beam;
	player_dir = data->player->direction;
	cam->beam.len = len[side_hit];
	if (side_hit == _x)
	{
		if (ray.direction.y > 0)
			cam->beam.side = NORTH;
		else
			cam->beam.side = SOUTH;
	}
	else
	{
		if (ray.direction.x < 0)
			cam->beam.side = EAST;
		else
			cam->beam.side = WEST;
	}
	cam->beam.hit_point = ray_position[side_hit];
	cam->beam.dist_from_plan = vectors_angle_cos(ray.direction, player_dir) * cam->beam.len;
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
	set_beam(data, &ray_position, &len);
	wall_hit = first_step(data, &ray_position, &len);
	while (wall_hit == -1)
		wall_hit = beam_step(data, &ray_position, &len);
	raysult(data, ray_position, len, wall_hit);
	return (cam->beam);
}

void	set_arRay(t_data *data)
{
	t_ray	ray;
	t_cam	*cam;
	int		i_ray;

	init_cam_vector(data);
	cam = data->cam;
	ray = cam->beam;
	i_ray = 0;
	while (i_ray < CAM_QUALITY)
	{
		cam->arRay[i_ray] = beam(data);
		translate_vector_as_pt(cam->plane_dir, &ray.direction);
		i_ray++;
	}
}
