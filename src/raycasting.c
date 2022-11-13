/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suplayerko <suplayerko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:17:56 by suplayerko          #+#    #+#             */
/*   Updated: 2022/11/13 16:14:47 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_beam(t_data *data, t_obstacle **obstacles_ls)
{
	set_delta_distance(data);
	set_side_distance(data);
	*obstacles_ls = NULL;
}

double get_dist_from_plan(t_data *data, t_rayturned *rayturned)
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
	return (distance_line_to_point(line, rayturned->hit_point));
}

int	get_side_hit(t_data *data, int index_closest)
{
	t_ray	*ray;
	
	ray = data->cam->beam;
	if (index_closest == _y)
	{
		if (ray->direction.y > 0)
			return (SOUTH);
		else
			return (NORTH);
	}
	else
	{
		if (ray->direction.x > 0)
			return (EAST);
		else
			return (WEST);
	}
}

int	len_overflow(int len)
{
	if (len < 0 || len > 2000000000)
		return (1);
	return (0);
}

t_obstacle	*add_obstacle(t_data *data, t_rayturned r, char m_case, t_obstacle **ls)
{
	t_obstacle		*obstacle;

	obstacle = ft_lstnew(r, m_case);
	if (!obstacle)
		clean_exit(data, -1);
	if (m_case == SPRITE)
	{
		obstacle->side = -1;
		obstacle->hit_point.x = -1;
		obstacle->hit_point.y = -1;
	}
	else
	{
		obstacle->sprite_hit = -1;
		obstacle->sprite_pointer = NULL;
	}
	ft_lstadd_front(ls, obstacle);
	return (obstacle);
}

t_obstacle	*insert_sort_obstacle(t_obstacle **ls, t_obstacle *new_itm)
{
	t_obstacle	*tmp;
	t_obstacle	*last_tmp;

	last_tmp = NULL;
	if (!*ls)
		*ls = new_itm;
	else if (new_itm)
	{
		tmp = *ls;
		while (tmp && new_itm->len < tmp->len)
		{
			last_tmp = tmp;
			tmp = tmp->next;
		}
		new_itm->next = tmp;
		if (last_tmp)
			last_tmp->next = new_itm;
		else
			*ls = new_itm;
	}
	return (*ls);
}

t_obstacle	*sort_obstacles(t_obstacle **ls)
{
	t_obstacle	*min_len;
	t_obstacle	*new_list;
	t_obstacle	*tmp;
	double		min_value;

	if (ls && *ls)
	{
		tmp = *ls;
		min_value = tmp->len;
		min_len = tmp;
		while (tmp)
	}
}

t_rayturned	next_wall_dir(t_data *data, int dir, t_obstacle **obstacles_ls)
{
	t_cam			*cam;
	t_ray			ray;
	t_vector		vect;
	t_rayturned		rayturned;
	char			map_case;

	cam = data->cam;
	ray = *(cam->beam);
	rayturned.len = ray.side_distances[dir];
	while (!len_overflow(rayturned.len))
	{
		vect = vec_scale(ray.direction, rayturned.len / ray.direction_len);
		rayturned.hit_point = translate_pt(vect, data->player->pos_in_pix);
		if (still_in_map(data, rayturned.hit_point))
		{
			map_case =  pix_pos_to_map_case(data, rayturned.hit_point);
			if (map_case == WALL)
				break ;
			else if (is_block(data, map_case) != -1)
			{
				add_obstacle(data, rayturned, map_case, obstacles_ls);
				(*obstacles_ls)->side = get_side_hit(data, dir);
			}
		}
		else
		{
			rayturned.len = 2147483647;
			break ;
		}
		rayturned.len += ray.delta_distances[dir];
	}
	return (rayturned);
}

void	convert_pos_and_dir_to_line(t_point pos, t_vector vec, t_vector line[2])
{
	t_vector	v_pos;

	v_pos.x = (double)pos.x;
	v_pos.y = (double)pos.y;
	line[0] = v_pos;
	translate_vector_as_pt(vec, &v_pos);
	line[1] = v_pos;
}

void	beam(t_data *data, t_rayturned *rayturned)
{
	t_rayturned	rays[2];
	int			index_closest;
	t_obstacle	*obstacles_ls;

	set_beam(data, &obstacles_ls);
	rays[_x] = next_wall_dir(data, _x, &obstacles_ls);
	rays[_y] = next_wall_dir(data, _y, &obstacles_ls);
	index_closest = _x;
	if (rays[_x].len > rays[_y].len)
		index_closest = _y;
	*rayturned = rays[index_closest];
	rayturned->side = get_side_hit(data, index_closest);
	rayturned->dist_from_plan = get_dist_from_plan(data, rayturned);
	add_sprites(data, rayturned, &obstacles_ls);
	rayturned->obstacles_ls = obstacles_ls;
}

void	set_arRay(t_data *data)
{
	t_ray		*ray;
	t_cam		*cam;
	int			i_ray;
	t_rayturned	rayturned;

	init_cam_vector(data);
	cam = data->cam;
	ray = cam->beam;
	i_ray = 0;
	while (i_ray < CAM_QUALITY)
	{
		beam(data, &rayturned);
		cam->arRay[i_ray] = rayturned;
		translate_vector_as_pt(cam->plane_dir, &ray->direction);
		i_ray++;
	}
}
