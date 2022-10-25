/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <ndionis@student.42mulhouse.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:17:56 by supersko          #+#    #+#             */
/*   Updated: 2022/10/25 13:07:39 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_person	*default_person(void)
{
	t_person	*pers;

	pers = malloc(sizeof(t_person));
	pers->pos.x = 22;
	pers->pos.y = 12;
	pers->dir.x = -1;
	pers->dir.y = 0;
	pers->plane.x = 0;
	pers->plane.y = 0.66;
	return (pers);
}

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

void	ray_parse(t_s *s)
{
	int			i;
	int			x_cam;
	t_pt		v_dir;
	t_person	*pers;

	(void)v_dir;
//cameraX is the x-coordinate on the camera plane that the current x-coordinate of the screen represents, done this way so that the right side of the screen will get coordinate 1
	pers = s->p;
	i = 0;
	while (i < RAYCAST_QUALITY)
	{
		//calculate ray position and direction
		x_cam = 2 * i / RAYCAST_QUALITY - 1; //x-coordinate in camera space
		v_dir.x = pers->dir.x + pers->plane.x * x_cam;
		v_dir.y = pers->dir.y + pers->plane.y * x_cam;
		i++;
	/*
	 deltaDistX = abs(1 / rayDirX)
	deltaDistY = abs(1 / rayDirY)
	*/
	}
}

void	clean_exit(t_s *s, int exit_code)
{
	if (s)
	{
		if (s->line)
			free(s->line);
		if (s->line_split)
			ft_free_split(&s->line_split);
		if (s->map)
			ft_free_split(&s->map);
		if (s->p)
			free(s->p);
		if (s->i)
			free(s->i);
		free(s);
	}
	exit(exit_code);
}

void	exit_msg(t_s *s, char *msg, int ret_exit)
{
	error_msg(msg);
	clean_exit(s, ret_exit);
}

int	main(int argc, char *argv[])
{
	t_imgg	img;
	t_s		*s;

	(void)img;
	(void)argv;
	s = NULL;
	if (argc != 2)
	{
		error_msg("Needs a path to the map file only");
		clean_exit(s, -2);
	}
	else
	{
		s = malloc(sizeof(t_s));
		if (!s)
			clean_exit(s, -4);
		s->i = malloc(sizeof(t_imgg));
		if (!s->i)
			clean_exit(s, -5);
		if (parse_file(argv[1], s) == -1)
			clean_exit(s, -3);
		//s->map = default_map(argv);
		/*
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
		print_tab(s->map);
		ft_free_split(&s->map);
	}
	exit (0);
}
