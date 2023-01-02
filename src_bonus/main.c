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

#include "../include/cub3d.h"

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
	srand(time(NULL));
		data = malloc_data();
		data->window = malloc(sizeof(t_window));
		data->window->mlx = mlx_init();
		parse_file(argv,  data);
		data->mouse = 0;
		free(argv);
		data->time_state = 0;
		data->door.state = 0;
		data->switcher.state = 0;
		data->minimap.state = 0;
		data->door.done = 0;
		data->switcher.done = 0;
		data->minimap.done = 0;
		data->map_height = 0;
		data->map_width = 0;
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
		return (0);
}

int g_status;

int	main(int argc, char *argv[])
{
	t_data		*data;


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
