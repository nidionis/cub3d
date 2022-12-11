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

void generate_map_content(t_data *data, char c)
{
	int y;
	int x;
	int wall_side;


	wall_side = 0;
	if (wall_side == 0)
	{
		x = rand() % data->map_width;
		y = 0;
	}
	else if (wall_side == 1)
	{
		x = rand() % data->map_width;
		y = data->map_height - 1;
	}
	else if (wall_side == 2)
	{
		x = 0;
		y = rand() % data->map_height;
	}
	else
	{
		x = data->map_width - 1;
		y = rand() % data->map_height;
	}
	if (data->map[y] && data->map[y][x])
		data->map[y][x] = c;
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
		parse_file(argv[1],  data);
		data->mouse = 0;
		data->time_state = 0;
		init_key_status(data);
		load_window(data);
		get_map_size(data);
		generate_map_content(data, 'P');
		data->rain_state = rand() % 5;
		//data->blocks[1] = 'P';
		//data->blocks[2] = '3';
		printf("%s\n",data->blocks);
		import_bonus_textures(data);
		import_sprites_textures(data);
		cub3d_render(data);
		clean_exit(data, 0);
	}
}
