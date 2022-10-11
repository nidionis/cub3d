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

#include <fractol.h>

static void	help_msg(void)
{
	error_msg("\n\
	Mandelbrot or Julia ? [M/j]\n\n\
	command help :\n\
		q - a : quality\n\
		w - s : color selection\n\
		e - d : modify real part of Julia's fractale\n\
		r - f : modify imaginary part of \"   \"\n\
		z     : Is it an available bonus ?\n");
}

int	main(int argc, char *argv[])
{
	t_imgg	img;

	if (argc <= 1 || argc > 2)
		help_msg();
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
}
