/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suplayerko <suplayerko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:17:56 by suplayerko          #+#    #+#             */
/*   Updated: 2022/12/01 17:56:36 by supersko         ###   ########.fr       */
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

void load_player(t_data *data)
{
	int i = 0;
	int j = 0;

	while (data->map[i])
	{
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'E')
			{
				data->player->direction.x = 1;
				data->player->direction.y = 0;
				data->player->pos_map.x = j;
				data->player->pos_map.y = i;
				data->player->pos_box.x = UNITS_PER_BOX / 2;
				data->player->pos_box.y = UNITS_PER_BOX / 2;
				data->player->pos_in_step = update_pos_in_step(data->player);
				data->player->pos_in_pix = update_pos_in_pix(data->player);
				data->player->speed = 1;
				data->player->rotate_speed = 1;
				data->player->map_pos.x = j;
				data->player->map_pos.y = i;
			}
			j++;
		}
		j = 0;
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_image		img;
	t_data		*data;
	(void)argv;
	(void)argc;
	(void)img;
	data = NULL;
	t_texture	t;

	t.path = argv[1];
	set_texture_size(&t);
	printf("%d %d\n", t.size[0], t.size[1]);
		/*
	if (argc != 2)
	{
		error_msg("Needs a path to the map file only");
		clean_exit(data, -2);
	}
	else
	{

		data = malloc_data();
		parse_file(argv[1],  data);
		data->window = malloc(sizeof(t_window));
		// load_player(data);
		init_key_status(data);
		window_init(data);
		cub3d_render(data);
		clean_exit(data, 0);
	}
		*/
}
