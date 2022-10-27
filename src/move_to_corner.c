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

void	slide_closest_box(t_player *p, int closest_box)
{
	if (closest_box == NORTH)
	{
		p->pos_map.y -= 1;
		p->pos_box.y = UNITS_PER_BOX - 1;
	}
	else if (closest_box == SOUTH)
	{
		p->pos_map.y += 1;
		p->pos_box.y = 0;
	}
	else if (closest_box == EAST)
	{
		p->pos_map.x -= 1;
		p->pos_box.x = UNITS_PER_BOX - 1;
	}
	else if (closest_box == WEST)
	{
		p->pos_map.x += 1;
		p->pos_box.x = 0;
	}
}

int	get_smallest_index(double wall_distance[4])
{
	int 	i;
	int 	smallest_index;
	double	last_smallest;

	last_smallest = wall_distance[0];
	smallest_index = 0;
	i = 1;
	while (i < 4)
	{
		if (wall_distance[i] < last_smallest)
			smallest_index = i;
		i++;
	}
	return (smallest_index);
}

/* https://en.wikipedia.org/wiki/Distance_from_a_point_to_a_line */
/* double	distance_point_to_vector(t_point point, t_point v_p1, t_point v_p2) */
int	check_closest_box(t_player *player)
{
	double	wall_distance[4];
	t_point	corner_NE;
	t_point	corner_NW;
	t_point	corner_SE;
	t_point	corner_SW;

	corner_NE = make_point(0, 0);
	corner_NW = make_point(0, UNITS_PER_BOX - 1);
	corner_SW = make_point(UNITS_PER_BOX - 1, UNITS_PER_BOX - 1);
	corner_SE = make_point(UNITS_PER_BOX - 1, 0);
	wall_distance[NORTH] = abs(distance_point_to_vector(player->pos_box, corner_NE, corner_NW));
	wall_distance[SOUTH] = abs(distance_point_to_vector(player->pos_box, corner_SE, corner_SW));
	wall_distance[EAST] = abs(distance_point_to_vector(player->pos_box, corner_NE, corner_SE));
	wall_distance[WEST] = abs(distance_point_to_vector(player->pos_box, corner_NW, corner_SW));
	return (get_smallest_index(wall_distance));
}

/* see case: 3 */
int	corner_crossing(t_data *data)
{
	t_player	*p;
	t_point		mp;
	char		**map;
	int			hit_wall;
	int			closest_box;

	p = data->player;
	mp.x = p->pos_map.x;
	mp.y = p->pos_map.y;
	map = data->map;
	hit_wall = 0;
	if (map[mp.y][mp.x] == WALL)
	{
		closest_box = check_closest_box(p);
		slide_closest_box(p, closest_box);
		hit_wall = 1;
	}
	return (hit_wall);
}
