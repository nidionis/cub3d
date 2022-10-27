/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suplayerko <suplayerko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:17:56 by suplayerko          #+#    #+#             */
/*   Updated: 2022/10/26 17:37:25 by suplayerko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
The algo check if the final position is overjump than the box size (or under 0 if going to the NORTH or WEST)
It refreshs the positions values in the map

In theses examples, player's step brings her to *
case 0:
 ____ ___ 
|    |    |
|WALL|    |
|    |*   |
L____|____|
|    |    |
|    |p   | player : box_position = { 0, 1 }
|    |    |			 map_position = { 1, 1 }
L____|____|

No wall:
	Box_position with UNITS_PER_BOX difference is applyed
	Map_position is updated

ex : player.box_position.y become -1
=>  new box position is :
		player.box_position.y = -1 + (UNITS_PER_BOX - 1)
Map_position.y decrease (or increase)
We apply the same concept for east-west axe

case 1:
 ____ ____
|WALL|    |
|    |    |
|    |*   |
L____|____|
|  p |$   |
|    |    |
|    |    |
L____|____|

When the next box (NSEW) is a wall, the values
payers.box_position[x] (or y) are set to 0 (or UNITS_PER_BOX - 1)
player arrive at $

case 2:
 ____ ____
|    |WALL|
|    |    |
|*   |    |
L____|____|
|$   |    |
|    |p   |
|    |    |
L____|____|
In this case, p want to reach *
North is a wall, so var is set to 0
map_case {1, 0} is not a wall, pers can jump out there
Player arrive at $

case 3:
 ____ ____
|WALL|    |
|    |    |
|   *|$   |
L____|____|
|    |    |
|    |p   |
|    |    |
L____|____|
In this case, p want to reach *
Player is not blocked buy walls north or west
The destination is still a wall
Find the closest adjacent box and arrive at $
*/

static int	f_is_box_crossed(t_player *player)
{
	int	direction;

	direction= 0;
	if (player->pos_box.y < 0)
		direction += N;
	if (player->pos_box.y >= POINTS_PER_BOX)
		direction += S;
	if (player->pos_box.x < 0)
		direction += E;
	if (player->pos_box.x >= POINTS_PER_BOX)
		direction += W;
	return (direction);
}

int	check_wall(t_data *data, int crossover_direction)
{
	int		hit_wall;

	hit_wall = 0;
	if (crossover_direction == N || crossover_direction == NE || crossover_direction == NW)
		hit_wall += north_crossing(data);
	if (crossover_direction == S || crossover_direction == SE || crossover_direction == SW)
		hit_wall += south_crossing(data);
	if (crossover_direction == E || crossover_direction == SE || crossover_direction == NE)
		hit_wall += east_crossing(data);
	if (crossover_direction == W || crossover_direction == Nw || crossover_direction == SW)
		hit_wall += west_crossing(data);
	if (!hit_wall)
	{
		if (crossover_direction == NE ||crossover_direction == SW || crossover_direction == NW || crossover_direction == SE)
			hit_wall = corner_crossing(data);
	}
	fprintf(stderr, "check_wall: hit_wall = %d\n", hit_wall);
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
	{
		hit_wall += check_wall(data, has_cross_over);
	}
	return (hit_wall);
}

int	move_player(t_data *data, int direction)
{
	int			hit_wall;
	t_player	*p;
	t_vector	*direction;

	p = data->player;
	scaled_direction = vec_scale(p->scaled_direction, (double)(POINTS_PER_BOX / STEPS_PER_BOX));
	//if (scaled_direction == FORWARD)
	if (scaled_direction == BACKWARD)
		rotate_vector(scaled_direction, degree_to_radian(180);
	else if (scaled_direction == RIGHT)
		rotate_vector(scaled_direction, degree_to_radian(90);
	else if (scaled_direction == LEFT)
		rotate_vector(scaled_direction, degree_to_radian(-90);
	translate_pt(scaled_direction, &p->pos_box);
	hit_wall = check_update_box_pos(data);
 	return (hit_wall);
 }
