/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 17:25:15 by supersko          #+#    #+#             */
/*   Updated: 2023/01/02 12:57:32 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub3d_bonus.h"

t_list	*make_obstacle(t_data *data, t_rayponse ray, char map_case, int dir)
{
	t_obstacle	*obst;
	t_list		*item;
	int			i_texture;

	obst = malloc(sizeof(t_obstacle));
	if (!obst)
		exit_msg(data, "[make_obstacle] pb adding obstacle", 1);
	ray.side = get_side_hit(data, dir);
	i_texture = (map_case - '2') * 4;
	obst->dist = get_dist_from_plan(data, &ray);
	obst->textureX = get_wallx(&ray);
	obst->texture = &data->bonus_textures[i_texture];
	item = ft_lstnew((void *)obst);
	if (!item)
		exit_msg(data, "[make_obstacle] pb adding obstacle", 2);
	return (item);
}

t_point	refresh_hit_point(t_data *data, t_rayponse *rayponse)
{
	return (translate_pt(vec_scale(data->cam->beam->direction, \
			rayponse->len / data->cam->beam->direction_len), \
				data->player->pos_in_pix));
}

t_rayponse	next_wall_dir(t_data *data, int dir, t_list **obstacles_ls)
{
	t_rayponse		rayponse;
	char			map_case;

	rayponse.len = data->cam->beam->side_distances[dir];
	while (!len_overflow(rayponse.len))
	{
		rayponse.hit_point = refresh_hit_point(data, &rayponse);
		if (still_in_map(data, rayponse.hit_point))
		{
			map_case = pix_pos_to_map_case(data, rayponse.hit_point);
			if (map_case == WALL)
				break ;
			else if (is_block(data, map_case) != -1)
				ft_lstadd_front(obstacles_ls, \
					make_obstacle(data, rayponse, map_case, dir));
		}
		else
		{
			rayponse.len = 2147483647;
			break ;
		}
		rayponse.len += data->cam->beam->delta_distances[dir];
	}
	return (rayponse);
}

void	beam(t_data *data, t_rayponse *rayponse)
{
	t_rayponse	rays[2];
	int			index_closest;
	t_list		*obstacles_ls;

	set_beam(data, &obstacles_ls);
	rays[_x] = next_wall_dir(data, _x, &obstacles_ls);
	rays[_y] = next_wall_dir(data, _y, &obstacles_ls);
	index_closest = _x;
	if (rays[_x].len > rays[_y].len)
		index_closest = _y;
	*rayponse = rays[index_closest];
	rayponse->side = get_side_hit(data, index_closest);
	rayponse->dist_from_plan = get_dist_from_plan(data, rayponse);
	sort_obstacles(&obstacles_ls);
	clean_obstacle_behind_wall(&obstacles_ls, rayponse->dist_from_plan);
	rayponse->obstacles_ls = obstacles_ls;
}

void	set_array(t_data *data)
{
	t_ray		*ray;
	t_cam		*cam;
	int			i_ray;
	t_rayponse	rayponse;

	init_cam_vector(data);
	cam = data->cam;
	ray = cam->beam;
	i_ray = 0;
	while (i_ray < data->window->width)
	{
		beam(data, &rayponse);
		cam->array[i_ray] = rayponse;
		translate_vector_as_pt(cam->plane_dir, &ray->direction);
		i_ray++;
	}
}
