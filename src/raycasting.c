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

void	set_beam(t_data *data)
{
	set_delta_distance(data);
	set_side_distance(data);
}

void set_dist_from_plan(t_data *data)
{
	t_vector	cam_dir;
	t_vector	v_pos;
	t_vector	line[2];

	cam_dir = data->cam->plane_dir;
	v_pos.x = (double)data->player->pos_in_pix.x;
	v_pos.y = (double)data->player->pos_in_pix.y;
	line[0] = v_pos;
	translate_vector_as_pt(cam_dir, &v_pos);
	line[1] = v_pos;
	data->cam->beam->dist_from_plan = distance_line_to_point(line, 	data->cam->beam->hit_point);
}

int	len_overflow(int len)
{
	if (len < 0 || len > 2000000000)
		return (1);
	return (0);
}

t_ray	next_wall_dir(t_data *data, int dir)
{
	t_cam		*cam;
	t_ray		ray;
	t_vector	vect;

	cam = data->cam;
	ray = *(cam->beam);
	ray.len = ray.side_distances[dir];
	while (!len_overflow(ray.len))
	{
		vect = vec_scale(ray.direction, ray.len / ray.direction_len);
		ray.hit_point = translate_pt(vect, data->player->pos_in_pix);
		if (still_in_map(data, ray.hit_point))
		{
			if (pix_pos_to_map_case(data, ray.hit_point) == WALL)
				break ;
		}
		else
		{
			ray.len = 2147483647;
			break ;
		}
		ray.len += ray.delta_distances[dir];
	}
	return (ray);
}

void	set_side_hit(t_data *data, int index_closest)
{
	t_ray	*ray;
	
	ray = data->cam->beam;
	if (index_closest == _y)
	{
		if (ray->direction.y > 0)
			ray->side = SOUTH;
		else
			ray->side = NORTH;
	}
	else
	{
		if (ray->direction.x > 0)
			ray->side = EAST;
		else
			ray->side = WEST;
	}
}

/*
	return absulute point (in UNIT_PER_BOX) hitting the wall
	delta_distance must be set before side distance
*/
void	beam(t_data *data)
{
	t_cam	*cam;
	t_ray	rays[2];
	int		index_closest;

	cam = data->cam;
	set_beam(data);
	rays[_x] = next_wall_dir(data, _x);
	rays[_y] = next_wall_dir(data, _y);
	index_closest = _x;
	if (rays[_x].len > rays[_y].len)
		index_closest = _y;
	*(cam->beam) = rays[index_closest];
	set_side_hit(data, index_closest);
	set_dist_from_plan(data);
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
		beam(data);
		cam->arRay[i_ray] = *ray;
		translate_vector_as_pt(cam->plane_dir, &ray->direction);
		i_ray++;
	}
}
