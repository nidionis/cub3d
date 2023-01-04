/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:17:56 by suplayerko        #+#    #+#             */
/*   Updated: 2023/01/04 17:44:06 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	player_smoth_move(t_data *data)
{
	static int	counter;
	static int	counter2;

	if (data->player->speed == 1 && data->player->stamina > 0)
	{
		counter++;
		if (counter == 5)
		{
			counter = 0;
			data->player->stamina--;
		}
	}
	else if (data->player->speed == 0 && data->player->stamina < 100)
	{
		counter2++;
		if (counter2 == 15)
		{
			counter2 = 0;
			data->player->stamina++;
		}
	}
	if (data->player->speed == 1 && data->player->stamina <= 0)
		data->player->speed = 0;
	direction_move(data);
}

int	move_player(t_data *data, int move)
{
	int			hit_wall;
	t_player	*p;
	t_vector	scaled_direction;

	p = data->player;
	if (data->player->speed == 1)
		scaled_direction = vec_scale(p->direction, \
			(double)(UNITS_PER_BOX / 15));
	else
		scaled_direction = vec_scale(p->direction, \
			(double)(UNITS_PER_BOX / STEPS_PER_BOX));
	if (move == BACKWARD)
		rotate_vector(&scaled_direction, degree_to_radian(180));
	else if (move == RIGHT)
		rotate_vector(&scaled_direction, degree_to_radian(90));
	else if (move == LEFT)
		rotate_vector(&scaled_direction, degree_to_radian(-90));
	translate_pt_inplace(scaled_direction, &p->pos_box);
	hit_wall = check_update_box_pos(data);
	update_pos_in_step(p);
	update_pos_in_pix(p);
	return (hit_wall);
}
