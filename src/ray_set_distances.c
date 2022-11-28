/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_set_distances.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 17:40:25 by supersko          #+#    #+#             */
/*   Updated: 2022/11/28 12:40:15 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_delta_distance(t_data *data)
{
	t_ray	*ray;
	t_cam	*cam;
	double	u;

	cam = data->cam;
	ray = cam->beam;
	u = (double)UNITS_PER_BOX;
	ray->direction_len = vec_len(ray->direction);
	if (fabs(ray->direction.x) > 0.000000001)
		ray->delta_distances[_x] = \
							ray->direction_len * u / fabs(ray->direction.x);
	else
		ray->delta_distances[_x] = 1000000000;
	if (fabs(ray->direction.y) > 0.000000001)
		ray->delta_distances[_y] = \
							 ray->direction_len * u / fabs(ray->direction.y);
	else
		ray->delta_distances[_y] = 2147483647;
}

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
		ray->side_distances[_x] = \
			ray->delta_distances[_x] * ((double)(u - player->pos_box.x) / u);
	else
		ray->side_distances[_x] = \
			ray->delta_distances[_x] * ((double)(1 + player->pos_box.x) / u);
	if (ray->direction.y > 0)
		ray->side_distances[_y] = \
			ray->delta_distances[_y] * ((double)(u - player->pos_box.y) / u);
	else
		ray->side_distances[_y] = \
			ray->delta_distances[_y] * ((double)(1 + player->pos_box.y) / u);
}
