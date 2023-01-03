/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 10:05:09 by dpaulino          #+#    #+#             */
/*   Updated: 2023/01/03 10:05:21 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub3d_bonus.h"

int	f_is_box_crossed(t_player *player)
{
	int	direction;

	direction = 0;
	if (player->pos_box.y < 0)
		direction += N;
	if (player->pos_box.y >= UNITS_PER_BOX)
		direction += S;
	if (player->pos_box.x < 0)
		direction += E;
	if (player->pos_box.x >= UNITS_PER_BOX)
		direction += W;
	return (direction);
}

int	update_pos_if_wall(t_data *data, int crossover_direction)
{
	int		hit_wall;

	hit_wall = 0;
	if (crossover_direction == N || crossover_direction \
	== NE || crossover_direction == NW)
		hit_wall += north_crossing(data);
	if (crossover_direction == S || crossover_direction \
	== SE || crossover_direction == SW)
		hit_wall += south_crossing(data);
	if (crossover_direction == E || crossover_direction == \
	SE || crossover_direction == NE)
		hit_wall += east_crossing(data);
	if (crossover_direction == W || crossover_direction == \
	NW || crossover_direction == SW)
		hit_wall += west_crossing(data);
	if (!hit_wall)
	{
		if (crossover_direction == NE || crossover_direction \
	== SW || crossover_direction == NW || crossover_direction \
	== SE)
			hit_wall = corner_crossing(data);
	}
	return (hit_wall);
}

/* return 1 if same, 2 if changed boxes, 0 if hit a wall) */
int	check_update_box_pos(t_data *data)
{
	int	has_cross_over;
	int	hit_wall;

	hit_wall = 0;
	has_cross_over = f_is_box_crossed(data->player);
	if (has_cross_over)
		hit_wall += update_pos_if_wall(data, has_cross_over);
	return (hit_wall);
}

void	direction_move(t_data *data)
{
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
}