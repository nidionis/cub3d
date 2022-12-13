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

#include "cub3d.h"
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

// void	generate_map_border(char **map)
// {
// 
// }

void generate_map_content(t_data *data, t_assets *asset, char c)
{
	int y;
	int x;
	int wall_side;


	if (asset->done == 1)
		data->map[asset->pos.y][asset->pos.x] = '1';
	wall_side = rand() % 4;
	if (wall_side == 0)
	{
		x = rand() % data->map_width - 2;
		if (x <= 0)
			x = 1;
		y = 1;
		asset->side = NORTH;
	}
	else if (wall_side == 1)
	{
		x = rand() % data->map_width - 2;
		if (x <= 0)
			x = 1;
		y = data->map_height - 2;
		asset->side = SOUTH;
	}
	else if (wall_side == 3)
	{
		x = 1;
		y = rand() % data->map_height - 2;
		if (y <= 0)
			y = 1;
		asset->side = WEST;
	}
	else
	{
		x = data->map_width - 2;
		y = rand() % data->map_height - 2;
		if (y <= 0)
			y = 1;
		asset->side = EAST;
	}
	if (y < data->map_height && x < data->map_width)
	{
		if (data->map[y][x] != '2' && data->map[y][x] != '3' && data->map[y][x] != '5')
		{
			data->map[y][x] = c;
			asset->pos.x = x;
			asset->pos.y = y;
			asset->done = 1;
		}
	}
}

void get_map_size(t_data *data)
{
	int	i;

	i = 0;
	data->map_width = ft_strlen(data->map[0]);
	while (data->map[i])
	{
		i++;
	}
	data->map_height = i;
}

void ff_player(char **map, t_player *player)
{
	int y;
	int x;

	y = 0;
	x = 0;
	while(map[y])
	{
		while(map[y][x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'W' || map[y][x] == 'E' || map[y][x] == 'S')
			{
				player->pos_map.x = x;
				player->pos_map.y = y;
				player->pos_box.x = UNITS_PER_BOX / 2;
				player->pos_box.y = UNITS_PER_BOX / 2;
				player->pos_in_step = update_pos_in_step(player);
				player->pos_in_pix = update_pos_in_pix(player);
				return ;
			}
			x++;
		}
		x = 0;
		y++;
	}
}

// int load_sounds(t_data *data)
// {
// 	(void)data;
// 	return (0);
// }

// int load_sound_tracks(t_data *data)
// {
// 	data->soundtracks[0] = malloc(sizeof(Mix_Chunk));
// 	data->soundtracks[1] = malloc(sizeof(Mix_Chunk));
// 	data->soundtracks[2] = malloc(sizeof(Mix_Chunk));
// 	data->soundtracks[3] = malloc(sizeof(Mix_Chunk));
// 	data->soundtracks[0] = Mix_LoadWAV("menu.wav");
// 	data->soundtracks[1] = Mix_LoadWAV("gameplay.wav");
// 	data->soundtracks[2] = Mix_LoadWAV("gameover.wav");
// 	data->soundtracks[3] = Mix_LoadWAV("gameover.wav");
// 	return (0);
// }

int	main(int argc, char *argv[])
{
	t_data		*data;
	data = NULL;
	
	// Mix_HaltChannel(-1);
	// SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	// Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	// Mix_Pause(-1);
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
		ff_player(data->map, data->player);
		init_key_status(data);
		load_window(data);
		// load_sounds(data);
		// load_sound_tracks(data);
		// Mix_PlayChannel(-1, data->soundtracks[0], 0);
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
		clean_exit(data, 0);
	}
}
