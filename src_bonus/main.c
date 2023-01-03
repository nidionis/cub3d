/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suplayerko <suplayerko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:17:56 by suplayerko          #+#    #+#             */
/*   Updated: 2022/12/01 18:48:48 by supersko         ###   ########.fr       */
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

int re_run_game(t_data *data, char *argv)
{
	char	*tmp;
	t_data	*data2;

	tmp = ft_strdup(argv);
	free(argv);
	(void) data;
	// free_everything(data);
	srand(time(NULL));
	data2 = malloc_data();
	data2->window = malloc(sizeof(t_window));
	data2->window->mlx = mlx_init();
	data2->argv = ft_strdup(tmp);
	free(tmp);
	parse_file(data2->argv,  data2);
	data2->mouse = 0;
	data2->time_state = 0;
	data2->door.state = 0;
	data2->switcher.state = 0;
	data2->minimap.state = 0;
	data2->door.done = 0;
	data2->switcher.done = 0;
	data2->minimap.done = 0;
	data2->map_height = 0;
	data2->map_width = 0;
	// load_soundtrack(data,&data->soundtrack, "gameplay.wav");
	// play_soundtrack(data,&data->soundtrack);
	// stop_soundtrack(data,&data->soundtrack);
	update_player(data2->map, data2->player);
	init_key_status(data2);
	load_window(data2);
	get_map_size(data2);
	while(!check_path_door(data2,data2->player->pos_map.y, data2->player->pos_map.x) || \
	!check_path_switch(data2,data2->player->pos_map.y, data2->player->pos_map.x) || \
	!check_path_map(data2,data2->player->pos_map.y, data2->player->pos_map.x))
	{
		generate_map_content(data2,&data2->minimap,'5');
		generate_map_content(data2,&data2->switcher,'3');
		generate_map_content(data2, &data2->door,'2');
	}
	data2->rain_state = rand() % 5;
	import_bonus_textures(data2);
	cub3d_render(data2);
	return (0);
}

int g_status;

int	main(int argc, char *argv[])
{
	t_data		*data;

	(void)argv;
	g_status = 0;
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
		parse_file(argv[1],  data);
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
		data->argv = argv[1];
		// load_soundtrack(data,&data->soundtrack, "gameplay.wav");
		// play_soundtrack(data,&data->soundtrack);
		// stop_soundtrack(data,&data->soundtrack);
		update_player(data->map, data->player);
		init_key_status(data);
		load_window(data);
		get_map_size(data);
		while(!check_path_door(data,data->player->pos_map.y, data->player->pos_map.x) || \
		!check_path_switch(data,data->player->pos_map.y, data->player->pos_map.x) || \
		!check_path_map(data,data->player->pos_map.y, data->player->pos_map.x))
		{
			generate_map_content(data,&data->minimap,'5');
			generate_map_content(data,&data->switcher,'3');
			generate_map_content(data, &data->door,'2');
		}
		data->rain_state = rand() % 5;
		import_bonus_textures(data);
		cub3d_render(data);
	}
}
