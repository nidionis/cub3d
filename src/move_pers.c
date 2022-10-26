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
The algo check if the final position is over than the box size (or under 0 if going to the NORTH or WEST)
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

ex : player.box_position.y become -1
=>  new box position is :
		player.box_position.y = -1 + (UNITS_PER_BOX - 1)
Only y overflowed on a negative way
(or increase if going to south or east)
We can guess wich direction we must carry if there is a wall
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

case 3:
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
Player arrive at $

can solve to $ because the box is adjacent

case 4:
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

int	north_crossing(t_data *data)
{
	char	**map = data->map;
	t_point	*pos_map = &data->player->pos_map;
	t_point	*pos_box = &data->player->pos_box;

	if (map[pos_map->y - 1][pos_map->x] == WALL)
	{
		pos_box->y = 0;
		return (1);
	}
	else
	{
		pos_box->y += (int)POINTS_PER_BOX - 1;
		(pos_map->y)--;
		return (0);
	}
}

int	check_wall(t_data *data, int crossover_direction)
{
	int		hit_a_wall;

	hit_a_wall = 0;
	if (crossover_direction == N || crossover_direction == NE || crossover_direction == NW)
	{
		hit_a_wall += north_crossing(data);
	}
	fprintf(stderr, "check_wall: hit_wall = %d\n", hit_a_wall);
	return (hit_a_wall);
}

/* return 1 if same, 2 if changed boxes, 0 if hit a wall) */
int	check_update_box_pos(t_data *data)
{
	int	has_cross_over;
	int	hit_wall;

	hit_wall = 0;
	has_cross_over = f_is_box_crossed(data->player);
	fprintf(stderr, "check_update_box_pos: has_cross_over = %d\n", has_cross_over);
	if (has_cross_over)
	{
		hit_wall += check_wall(data, has_cross_over);
	}
	return (hit_wall);
}

void	move_player(t_data *data, int direction)
{
	t_player	*p;

	p = data->player;
	if (direction == FORWARD)
	{
		translate_pt(p->direction, &p->pos_box);
	}
	check_update_box_pos(data);
 	return ;
 }
 
