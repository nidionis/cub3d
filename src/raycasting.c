/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 17:25:15 by supersko          #+#    #+#             */
/*   Updated: 2022/11/25 11:08:18 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_rayponse	next_wall_dir(t_data *data, int dir, t_obstacle **obstacles_ls)
{
	t_cam			*cam;
	t_ray			ray;
	t_vector		vect;
	t_rayponse		rayponse;
	char			map_case;

	(void)obstacles_ls;
	cam = data->cam;
	ray = *(cam->beam);
	rayponse.len = ray.side_distances[dir];
	while (!len_overflow(rayponse.len))
	{
		vect = vec_scale(ray.direction, rayponse.len / ray.direction_len);
		rayponse.hit_point = translate_pt(vect, data->player->pos_in_pix);
		if (still_in_map(data, rayponse.hit_point))
		{
			map_case =  pix_pos_to_map_case(data, rayponse.hit_point);
			if (map_case == WALL)
				break ;
			//else if (is_block(data, map_case) != -1)
			//{
			//	add_obstacle(data, rayponse, map_case, obstacles_ls);
			//	(*obstacles_ls)->side = get_side_hit(data, dir);
			//}
		}
		else
		{
			rayponse.len = 2147483647;
			break ;
		}
		rayponse.len += ray.delta_distances[dir];
	}
	return (rayponse);
}



void	beam(t_data *data, t_rayponse *rayponse)
{
	t_rayponse	rays[2];
	int			index_closest;
	t_obstacle	*obstacles_ls;

	if (data->key_status->w == 1)
		move_player(data, FORWARD);
	if (data->key_status->s == 1)
		move_player(data, BACKWARD);
	if (data->key_status->a == 1)
		move_player(data, LEFT);
	if (data->key_status->d == 1)
		move_player(data, RIGHT);
	if (data->key_status->left == 1)
		rotate_player(data->player, LEFT);
	if (data->key_status->right == 1)
		rotate_player(data->player, RIGHT);
	set_beam(data, &obstacles_ls);
	rays[_x] = next_wall_dir(data, _x, &obstacles_ls);
	rays[_y] = next_wall_dir(data, _y, &obstacles_ls);
	index_closest = _x;
	if (rays[_x].len > rays[_y].len)
		index_closest = _y;
	*rayponse = rays[index_closest];
	rayponse->side = get_side_hit(data, index_closest);
	rayponse->side = get_side_hit(data, index_closest);
	rayponse->dist_from_plan = get_dist_from_plan(data, rayponse);
	//add_sprites_to_obstacles_ls(data, rayponse, &obstacles_ls);
	rayponse->obstacles_ls = sort_obstacles(&obstacles_ls);
}

void	set_arRay(t_data *data)
{
	t_ray		*ray;
	t_cam		*cam;
	int			i_ray;
	t_rayponse	rayponse;

	init_cam_vector(data);
	cam = data->cam;
	ray = cam->beam;
	i_ray = 0;
	while (i_ray < CAM_QUALITY)
	{
		beam(data, &rayponse);
		cam->arRay[i_ray] = rayponse;
		translate_vector_as_pt(cam->plane_dir, &ray->direction);
		i_ray++;
	}
}
