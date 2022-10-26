/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:17:56 by supersko          #+#    #+#             */
/*   Updated: 2022/10/26 16:48:19 by supersko         ###   ########.fr       */
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
//	t_vector		v_dir;
//
//	(void)v_dir;
////cameraX is the x-coordinate on the camera plane that the current x-coordinate of the screen represents, done this way so that the right side of the screen will get coordinate 1
//	player = data->player;
//	i = 0;
//	while (i < RAYCAST_QUALITY)
//	{
//		//calculate ray position and direction
//		x_cam = 2 * i / RAYCAST_QUALITY - 1; //x-coordinate in camera space
//		v_dir.x = player->dir.x + player->plane.x * x_cam;
//		v_dir.y = player->dir.y + player->plane.y * x_cam;
//		i++;
//	/*
//	 deltaDistX = abs(1 / rayDirX)
//	deltaDistY = abs(1 / rayDirY)
//	*/
//	}
//}

 t_data	*malloc_s(void)
{
	 t_data	* data;

	 data = malloc(sizeof(t_data));
	if (! data)
		clean_exit(data, -4);
	data->image = malloc(sizeof(t_image));
	if (!data->image)
		clean_exit(data, -5);
	data->player = malloc(sizeof(t_player));
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
		 data = malloc_s();
		if (!data->player)
			clean_exit(data, -5);
		parse_file(argv[1],  data);
		redir_debug_file_logs(data, "debug_file");
		/*
		img.mlx_ptr = mlx_init();
		//img_default_init(&img);
		img.win_ptr = mlx_new_window(img.mlx_ptr, \
			img.size[0], img.size[1], "cub3d");
		//set_win_center(&img);
		img.img_ptr = mlx_new_image(img.mlx_ptr, \
			img.size[0], img.size[1]);
		img.addr = mlx_get_data_addr(img.img_ptr, \
			&(img.bpp), &(img.line_len), &(img.endian));
		//img.f(&img);
		//mlx_hook(img.win_ptr, ON_DESTROY, 0, clean_exit, & data);
		mlx_put_image_to_window(img.mlx_ptr, img.win_ptr, img.img_ptr, 0, 0);
		mlx_key_hook(img.win_ptr, manage_keystroke, &img);
		mlx_mouse_hook(img.win_ptr, manage_mouse, &img);
		mlx_mouse_hook(img.win_ptr, manage_expose, &img);
		mlx_loop(img.mlx_ptr);
		print_map(data->map);
	*/
	}
	clean_exit(data, 0);
}
