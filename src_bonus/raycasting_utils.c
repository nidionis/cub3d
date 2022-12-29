/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 17:24:39 by supersko          #+#    #+#             */
/*   Updated: 2022/12/29 14:01:06 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	set_beam(t_data *data, t_list **obstacles_ls)
{
	set_delta_distance(data);
	set_side_distance(data);
	*obstacles_ls = NULL;
}

double	get_dist_from_plan(t_data *data, t_rayponse *rayponse)
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
	return (distance_line_to_point(line, rayponse->hit_point));
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
