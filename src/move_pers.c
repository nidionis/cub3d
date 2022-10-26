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
		pos_box->y += (int)POINTS_PER_BOX;
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
 
