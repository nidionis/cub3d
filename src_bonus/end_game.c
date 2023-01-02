/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:33:31 by dpaulino          #+#    #+#             */
/*   Updated: 2023/01/02 12:54:39 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub3d_bonus.h"

static int	one_step_forward(t_player *player_fictif)
{
	t_vector	scaled_direction;
	int			has_cross_over;

	scaled_direction = vec_scale(player_fictif->direction, \
		(double)(UNITS_PER_BOX / STEPS_PER_BOX));
	translate_pt_inplace(scaled_direction, &player_fictif->pos_box);
	has_cross_over = f_is_box_crossed(player_fictif);
	return (has_cross_over);
}

int	map_position_in_front_of_players(t_player *player)
{
	t_player	player_fictif;
	int			side_crossed;

	player_fictif = *player;
	side_crossed = one_step_forward(&player_fictif);
	while (!side_crossed)
		side_crossed = one_step_forward(&player_fictif);
	if (side_crossed == N || side_crossed == NE || side_crossed == NW)
		return (1);
	if (side_crossed == S || side_crossed == SE || side_crossed == SW)
		return (2);
	if (side_crossed == E || side_crossed == NE || side_crossed == SE)
		return (3);
	if (side_crossed == W || side_crossed == NW || side_crossed == SW)
		return (4);
	return (0);
}

int	check_north_south(t_player *player, t_assets *asset)
{
	if (asset->side == NORTH)
	{
		if (player->pos_map.x == asset->pos.x && player->pos_map.y - 1 == \
		asset->pos.y && map_position_in_front_of_players(player) == 1)
			return (1);
	}
	if (asset->side == SOUTH)
	{
		if (player->pos_map.x == asset->pos.x && player->pos_map.y + 1 == \
		asset->pos.y && map_position_in_front_of_players(player) == 2)
			return (1);
	}
	return (0);
}

int	end_game(t_data *data, t_assets *asset)
{
	t_player	*player;

	player = data->player;
	if (check_north_south(player, asset))
		return (1);
	if (asset->side == WEST)
	{
		if (player->pos_map.x - 1 == asset->pos.x && player->pos_map.y == \
		asset->pos.y && map_position_in_front_of_players(player) == 3)
			return (1);
	}
	if (asset->side == EAST)
	{
		if (player->pos_map.x + 1 == asset->pos.x && player->pos_map.y == \
		asset->pos.y && map_position_in_front_of_players(player) == 4)
			return (1);
	}
	return (0);
}
