/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:17:56 by suplayerko        #+#    #+#             */
/*   Updated: 2023/01/04 18:47:31 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub3d_bonus.h"

t_data	*malloc_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		clean_exit(data, -1);
	data->image = malloc(sizeof(t_image));
	if (!data->image)
		clean_exit(data, -1);
	data->player = malloc(sizeof(t_player));
	if (!data->player)
		clean_exit(data, -1);
	data->blocks = ft_strdup(IS_BLOCK);
	if (!data->blocks)
		clean_exit(data, -1);
	data->map_cases = ft_strdup(MAPCASES);
	if (!data->map_cases)
		clean_exit(data, -1);
	data->cam = malloc(sizeof(t_cam));
	if (!data->cam)
		clean_exit(data, -1);
	data->cam->beam = malloc(sizeof(t_ray));
	if (!data->cam->beam)
		clean_exit(data, -1);
	return (data);
}

void	init_gameplay_var(t_data *data)
{
	data->mouse = 0;
	data->time_state = 0;
	data->door.state = 0;
	data->switcher.state = 0;
	data->minimap.state = 0;
	data->door.done = 0;
	data->switcher.done = 0;
	data->minimap.done = 0;
	data->map_height = 0;
	data->map_width = 0;
}

void	re_generate_map(t_data *data)
{
	t_player	*player;

	player = data->player;
	while (!check_path_door(data, player->pos_map.y, player->pos_map.x) || \
		!check_path_switch(data, player->pos_map.y, player->pos_map.x) || \
		!check_path_map(data, player->pos_map.y, player->pos_map.x))
	{
		generate_map_content(data, &data->minimap, '5');
		generate_map_content(data, &data->switcher, '3');
		generate_map_content(data, &data->door, '2');
	}
}

int	main(int argc, char *argv[])
{
	t_data		*data;

	data = NULL;
	if (argc != 2)
	{
		error_msg("Needs a path to the map file only");
		clean_exit(data, -2);
	}
	else
	{
		srand(time(NULL));
		data = malloc_data();
		data->window = malloc(sizeof(t_window));
		data->window->mlx = mlx_init();
		parse_file(argv[1], data);
		init_gameplay_var(data);
		update_player(data->map, data->player);
		init_key_status(data);
		load_window(data);
		get_map_size(data);
		re_generate_map(data);
		data->rain_state = rand() % 5;
		import_bonus_textures(data);
		cub3d_render(data);
	}
}
