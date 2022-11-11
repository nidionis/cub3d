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
	t_ray	*ray;
	t_cam	*cam;
	double	u;

	cam = data->cam;
	ray = cam->beam;
	u = (double)UNITS_PER_BOX;
	ray->direction_len = vec_len(ray->direction);
	if (ray->direction.x)
		ray->delta_distances.x = ray->direction_len * u / fabs(ray->direction.x);
	else
		ray->delta_distances.x = 2147483647;
	if (ray->direction.y)
		ray->delta_distances.y = ray->direction_len * u / fabs(ray->direction.y);
	else
		ray->delta_distances.y = 2147483647;
	ray->vector_deltaX = vec_scale(ray->direction, ray->delta_distances.x / ray->direction_len);
	ray->vector_deltaY = vec_scale(ray->direction, ray->delta_distances.y / ray->direction_len);
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
