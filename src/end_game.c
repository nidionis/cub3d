#include "../include/cub3d.h"

static int	one_step_forward(t_player *player_fictif)
{
	t_vector	scaled_direction;
	int		has_cross_over;

	scaled_direction = vec_scale(player_fictif->direction, (double)(UNITS_PER_BOX / STEPS_PER_BOX));
	translate_pt_inplace(scaled_direction, &player_fictif->pos_box);
	has_cross_over = f_is_box_crossed(player_fictif);
	return (has_cross_over);
}

int	map_position_in_front_of_players(t_player *player)
{
	t_player	player_fictif;
	int		side_crossed;

	player_fictif = *player;
	// a fictif player go forward until he hit wall
	side_crossed = one_step_forward(&player_fictif);
	while(!side_crossed)
		side_crossed = one_step_forward(&player_fictif);
	if (side_crossed == N || side_crossed == NE || side_crossed == NW)
		return(1);
	if (side_crossed == S || side_crossed == SE || side_crossed == SW)
		return(2);
	if (side_crossed == E || side_crossed == NE || side_crossed == SE)
		return (3);
	if (side_crossed == W || side_crossed == NW || side_crossed == SW)
		return(4);
	return (0);
}

int	end_game(t_data *data)
{
	if (data->door.door_side == NORTH)
	{
		if (data->player->pos_map.x == data->door.pos.x && data->player->pos_map.y - 1 == data->door.pos.y\
				&& map_position_in_front_of_players(data->player) == 1)
			return (1);
	}
	else if (data->door.door_side == SOUTH)
	{
		if (data->player->pos_map.x == data->door.pos.x && data->player->pos_map.y + 1 == data->door.pos.y\
			   && map_position_in_front_of_players(data->player) == 2)
			return (1);
	}
	else if (data->door.door_side == WEST)
	{
		if (data->player->pos_map.x - 1 == data->door.pos.x && data->player->pos_map.y == data->door.pos.y\
				&& map_position_in_front_of_players(data->player) == 3)
			return (1);
	}
	else if (data->door.door_side == EAST)
	{
		if (data->player->pos_map.x + 1 == data->door.pos.x && data->player->pos_map.y == data->door.pos.y\
			   && map_position_in_front_of_players(data->player) == 4)
			return (1);
	}
	return (0);
}