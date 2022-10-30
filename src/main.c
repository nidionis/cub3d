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

/*
DDA algo
si |x2-x1| >= |y2-y1| alors
  longueur := |x2-x1|
sinon
  longueur := |y2-y1|
fin si
dx := (x2-x1) / longueur
dy := (y2-y1) / longueur
x := x1 + 0.5
y := y1 + 0.5
i := 1
tant que i ≤ longueur faire
  setPixel (E (x), E (y))
  x := x + dx
  y := y + dy
  i := i + 1
fin tant que

*/
//
//void	ray_parse(t_data *data)
//{
//	int			i;
//	int			x_cam;
//	t_player	*player;
//	t_vector		vdirection
//
//	(void)vdirection
////cameraX is the x-coordinate on the camera plane that the current x-coordinate of the screen represents, done this way so that the right side of the screen will get coordinate 1
//	player = data->player;
//	i = 0;
//	while (i < RAYCAST_QUALITY)
//	{
//		//calculate ray position and direction
//		x_cam = 2 * i / RAYCAST_QUALITY - 1; //x-coordinate in camera space
//		vdirectionx = player-directionx + player->plane.x * x_cam;
//		vdirectiony = player-directiony + player->plane.y * x_cam;
//		i++;
//	/*
//	 deltaDistX = abs(1 / rayDirX)
//	deltaDistY = abs(1 / rayDirY)
//	*/
//	}
//}

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

int	main(int argc, char *argv[])
{
	t_image	img;
	t_data		* data;

	(void)img;
	(void)argv;
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

		redir_debug_file_logs(data, DEBUG_LOG_FILENAME, CAM);
	init_cam_vector(data);		
		redir_debug_file_logs(data, DEBUG_LOG_FILENAME, CAM);
		redir_debug_file_logs(data, DEBUG_LOG_FILENAME, PLAYER);
		rotate_player(data->player, LEFT);
		redir_debug_file_logs(data, DEBUG_LOG_FILENAME, PLAYER);
		rotate_player(data->player, LEFT);
		redir_debug_file_logs(data, DEBUG_LOG_FILENAME, PLAYER);
		rotate_player(data->player, LEFT);
		redir_debug_file_logs(data, DEBUG_LOG_FILENAME, PLAYER);
		rotate_player(data->player, LEFT);
		redir_debug_file_logs(data, DEBUG_LOG_FILENAME, PLAYER);
		if (move_player(data, LEFT))
			redir_debug_file_msg(DEBUG_LOG_FILENAME, "\tWALLX");
		redir_debug_file_logs(data, DEBUG_LOG_FILENAME, PLAYER);
		if (move_player(data, LEFT))
			redir_debug_file_msg(DEBUG_LOG_FILENAME, "\tWALLX");
		redir_debug_file_logs(data, DEBUG_LOG_FILENAME, PLAYER);
		if (move_player(data, LEFT))
			redir_debug_file_msg(DEBUG_LOG_FILENAME, "\tWALLX");
		redir_debug_file_logs(data, DEBUG_LOG_FILENAME, PLAYER);
		if (move_player(data, LEFT))
			redir_debug_file_msg(DEBUG_LOG_FILENAME, "\tWALLX");
	}
}
