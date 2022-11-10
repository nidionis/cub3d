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
	double	u;
	
	cam = data->cam;
	ray = cam->beam;
	u = (double)UNITS_PER_BOX;
	ray->direction_len = vec_len(ray->direction);
	ray->delta_distances.x = ray->direction_len * u / fabs(ray->direction.x);
	ray->delta_distances.y = ray->direction_len * u / fabs(ray->direction.y);
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
	double		u;
	
	cam = data->cam;
	ray = cam->beam;
	player = data->player;
	u = (double)UNITS_PER_BOX;
	if (ray->direction.x > 0)
		ray->side_distances.x = ray->delta_distances.x * ((double)(u - player->pos_box.x) / u);
	else
		ray->side_distances.x = ray->delta_distances.x * ((double)(1 + player->pos_box.x) / u);
	if (ray->direction.y > 0)
		ray->side_distances.y = ray->delta_distances.y * ((double)(u - player->pos_box.y) / u);
	else
		ray->side_distances.y = ray->delta_distances.y * ((double)(1 + player->pos_box.y) / u);
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
	char	next_cases[2];
	int		closest;

	ray = data->cam->beam;
	closest = _y;
	len[_x] = ray->side_distances.x;
	len[_y] = ray->side_distances.y;
	if (len[_x] > 0 && len[_x] < len [_y])
		closest = _x;
	translate_pt(ray->vector_sideX, &ray_position[_x]);
	translate_pt(ray->vector_sideY, &ray_position[_y]);
	next_cases[closest] = pix_pos_to_map_case(data, ray_position[closest]);
	if (next_cases[closest] == WALL)
		return (closest);
	if (still_in_map(data, ray_position[!closest]))
		next_cases[!closest] = pix_pos_to_map_case(data, ray_position[!closest]);
	if (next_cases[!closest] == WALL)
		return (!closest);
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
		if (still_in_map(data, ray_position[_x]))
		{
			if (pix_pos_to_map_case(data, ray_position[_x]) == WALL)
				return (_x);
		} else if (!still_in_map(data, ray_position[_y]))
		{
			fprintf(stderr, "[beam] ray_lost\n");
			return (-2);
		}
	}
	else
	{
		translate_pt(ray->vector_deltaY, &ray_position[_y]);
		len[_y] += ray->delta_distances.y;
		if (still_in_map(data, ray_position[_y]))
		{
			if (pix_pos_to_map_case(data, ray_position[_y]) == WALL)
				return (_y);
		} else if (!still_in_map(data, ray_position[_x]))
		{
			fprintf(stderr, "[beam] ray_lost\n");
			return (-2);
		}
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
	if (side_hit == _y)
	{
		if (ray->direction.y > 0)
			ray->side = SOUTH;
		else
			ray->side = NORTH;
	}
	else
	{
		if (ray->direction.x < 0)
			ray->side = WEST;
		else
			ray->side = EAST;
	}
	ray->hit_point = ray_position[side_hit];
	cam_dir = data->cam->plane_dir;
	ray->dist_from_plan = vectors_angle_sin(cam_dir, ray->direction) * ray->len;
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
		wall_hit = beam_step(data, ray_position, len);
	}
	if (wall_hit != -2)
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
