/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:24:29 by supersko          #+#    #+#             */
/*   Updated: 2022/05/31 18:39:01 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	err_msg(char *msg, int fd)
{
	int	useless;

	useless = write(fd, "Error\n", 6);
	while (*msg)
		useless = write(fd, msg++, 1);
	useless = write(fd, "\n", 1);
	(void)useless;
}

int	main(int argc, char *argv[])
{
	t_imgg	img;
	(void)img;
	(void)argv;

	if (argc != 2)
		err_msg("Needs a path to the map file only", 1);
		/*
	else
	{
		img.mlx_ptr = mlx_init();
		img_default_init(&img);
		if ((argv[1][0] == 'j' || argv[1][0] == 'J') && !argv[1][1])
			img.f = julia;
		else
			img.f = mandelbrot;
	}
	img.win_ptr = mlx_new_window(img.mlx_ptr, \
		img.size[0], img.size[1], "fractol");
	set_win_center(&img);
	img.img_ptr = mlx_new_image(img.mlx_ptr, \
		img.size[0], img.size[1]);
	img.addr = mlx_get_data_addr(img.img_ptr, \
		&(img.bpp), &(img.line_len), &(img.endian));
	img.f(&img);
	mlx_put_image_to_window(img.mlx_ptr, img.win_ptr, img.img_ptr, 0, 0);
	mlx_hook(img.win_ptr, ON_DESTROY, 0, quit, &img);
	mlx_key_hook(img.win_ptr, manage_keystroke, &img);
	mlx_mouse_hook(img.win_ptr, manage_mouse, &img);
	mlx_mouse_hook(img.win_ptr, manage_expose, &img);
	mlx_loop(img.mlx_ptr);
	*/
}
