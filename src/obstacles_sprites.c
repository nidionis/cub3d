/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suplayerko <suplayerko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:17:56 by suplayerko          #+#    #+#             */
/*   Updated: 2022/11/13 15:13:12 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	not_behind(t_point origin, t_vector origin_direction, t_point target)
{
	int origin_target_direction;
	int	same_direction;

	same_direction = 0;
	origin_target_direction = target.x - origin.x;
	if ((origin_target_direction * origin_direction.x) > 0)
		same_direction = 1;
	origin_target_direction = target.y - origin.y;
	if ((origin_target_direction * origin_direction.y) > 0)
		same_direction = 1;
	return (same_direction);
}

/* returns -1 if not */
double	ray_cross_sprite(t_data *data, t_sprite *sprite, t_rayponse *rayponse)
{
	t_vector	ray_dir;
	t_vector	line[2];
	double		sprite_hit;
	t_point		player_pos;
	double		len;

	player_pos = data->player->pos_in_pix;
	sprite_hit = -1;
	ray_dir = data->cam->beam->direction;
	convert_pos_and_dir_to_line(data->player->pos_in_pix, ray_dir, line);
	len = distance_points(player_pos, sprite->pos);
	if (len < rayponse->len && not_behind(player_pos, ray_dir, sprite->pos))
	{
		sprite_hit = distance_line_to_point(line, sprite->pos);
		if ((int)sprite_hit >= data->image->sprite_half_size)
			sprite_hit = -1;
	}
	return (sprite_hit);
}

t_obstacle	*add_sprite(t_data *data, t_sprite *sprite, t_rayponse *rayponse, t_obstacle **obstacles_ls, double sprite_hit)
{
	double		len;
	t_point		player_pos;
	t_obstacle	*obstacle;

	player_pos = data->player->pos_in_pix;
	len = distance_points(player_pos, sprite->pos);
	obstacle = add_obstacle(data, *rayponse, SPRITE, obstacles_ls);
	obstacle->len = len;
	obstacle->sprite_hit = sprite_hit;
	obstacle->sprite_pointer = sprite;
	return (obstacle);
}

t_obstacle	*add_sprites_to_obstacles_ls(t_data *data, t_rayponse *rayponse, t_obstacle **obstacles_ls)
{
	t_sprite *sprite;
	double		sprite_hit;

	sprite = data->image->sprite_ls;
	while (sprite)
	{
		sprite_hit = ray_cross_sprite(data, sprite, rayponse);
		if (sprite_hit != -1)
			add_sprite(data, sprite, rayponse, obstacles_ls, sprite_hit);
		sprite = sprite->next;
	}
	return (*obstacles_ls);
}

