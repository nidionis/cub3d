/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suplayerko <suplayerko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:17:56 by suplayerko          #+#    #+#             */
/*   Updated: 2022/10/26 17:33:57 by suplayerko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

 t_data	*malloc_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		clean_exit(data, -4);
	data->image = malloc(sizeof(t_image));
	if (!data->image)
		clean_exit(data, -6);
	data->player = malloc(sizeof(t_player));
	if (!data->player)
		clean_exit(data, -7);
	data->blocks = ft_strdup(IS_BLOCK);
	if (!data->blocks)
		clean_exit(data, -8);
	data->map_cases = ft_strdup(MAPCASES);
	fprintf(stderr, "%s\n", data->map_cases);
	if (!data->map_cases)
		clean_exit(data, -9);
	return (data);
}

void	test_function(t_data *data)
{
	clean_useless_empty_splace(data->map);
	redir_debug_file_logs(data, DEBUG_LOG_FILENAME, MAP);
}

int	main(int argc, char *argv[])
{
	t_image		img;
	t_data		*data;

	(void)img;
	data = NULL;
	if (argc != 2)
	{
		error_msg("Needs a path to the map file only");
		clean_exit(data, -2);
	}
	else
	{
		data = malloc_data();
		parse_file(argv[1],  data);
		test_function(data);
		//data->window = malloc(sizeof(t_window));
		//window_init(data->window);
		//render_map_2d(data);
	}
}
