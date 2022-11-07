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

void	set_beam(t_data *data, t_vector (*ray_position)[2], double (*len)[2])
{
	(*ray_position)[_x] = convert_pt_to_vec(data->player->pos_in_pix);
	(*ray_position)[_y] = convert_pt_to_vec(data->player->pos_in_pix);
	set_delta_distance(data);
	set_side_distance(data);
	(*len)[_x] = data->cam->beam.side_distances.x;
	(*len)[_y] = data->cam->beam.side_distances.y;
}

int	first_step(t_data *data, t_vector (*ray_position)[2], double (*len)[2])
{
	t_ray	ray;

	ray = data->cam->beam;
	translate_vector_as_pt(ray.vector_sideX, ray_position[_x]);
	if (pix_pos_to_map_case((*ray_position)[_x]) == WALL)
		return (_x);
	translate_vector_as_pt(ray.vector_sideY, ray_position[_y]);
	if (pix_pos_to_map_case((*ray_position)[_y]) == WALL)
		return (_y);
	return (-1);
}

int	beam_steps(t_data *data, t_vector (*ray_position)[2], double (*len)[2])
{
	t_ray	ray;

	ray = data->cam->beam;
	if ((*len)[_x] < (*len)[_y])
	{
		translate_vector_as_pt(ray.vector_deltaX, ray_position[_x]);
		(*len)[_x] += ray.delta_distances.x;
		if (pix_pos_to_map_case((*ray_position)[_x]) == WALL)
			return (_x);
	}
	else
	{
		translate_vector_as_pt(ray.vector_deltaY, ray_position[_y]);
		(*len)[_y] += ray.delta_distances.y;
		if (pix_pos_to_map_case((*ray_position)[_y]) == WALL)
			return (_y);
	}
	return (-1);
}

void	raysult(t_ray *ray, t_vector ray_position[2], double len[2], int side_hit)
{
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
}

/*
	return absulute point (in UNIT_PER_BOX) hitting the wall
	delta_distance must be set before side distance
*/
t_ray	beam(t_data *data)
{
	t_vector	ray_position[2]; // x and y
	double		len[2];
	t_cam		*cam;
	int			wall_hit;

	cam = data->cam;
	set_beam(data, &ray_position, &len);
	wall_hit = first_step(data, &ray_position, &len);
	while (wall_hit == -1)
		wall_hit = beam_steps(data, &ray_position, &len);
	raysult(&cam->beam, ray_position, len, wall_hit);
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
