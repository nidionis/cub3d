#include <cub3d.h>

static int	one_step_forward(t_player *player_fictif)
{
	t_vector	scaled_direction;
	int		has_cross_over;

	scaled_direction = vec_scale(player_fictif->direction, (double)(UNITS_PER_BOX / STEPS_PER_BOX));
	translate_pt_inplace(scaled_direction, &player_fictif->pos_box);
	has_cross_over = f_is_box_crossed(player_fictif);
	return (has_cross_over);
}

t_point	map_position_in_front_of_player(t_player *player)
{
	t_player	player_fictif;
	int		side_crossed;
	t_point		p;

	player_fictif = *player;
	// a fictif player go forward until he hit wall
	side_crossed = one_step_forward(&player_fictif);
	while(!side_crossed)
		side_crossed = one_step_forward(&player_fictif);
	p = player->pos_map;
	if (side_crossed == N || side_crossed == NE || side_crossed == NW)
		p.y -= 1;
	if (side_crossed == S || side_crossed == SE || side_crossed == SW)
		p.y += 1;
	if (side_crossed == E || side_crossed == NE || side_crossed == SE)
		p.x += 1;
	if (side_crossed == W || side_crossed == NW || side_crossed == SW)
		p.x -= 1;
	return (p);
}
