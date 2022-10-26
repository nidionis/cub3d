/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:24:29 by supersko          #+#    #+#             */
/*   Updated: 2022/10/26 15:24:41 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

static void	foret_de_ifs(t_image *img, int keystroke)
{
	if (keystroke == KEY_Q)
	{
		if (img->quality < 60)
			(img->quality)++;
	}
	else if (keystroke == KEY_S && img->color_shift < 16)
		(img->color_shift)++;
	else if (keystroke == KEY_W && img->color_shift > 0)
		(img->color_shift)--;
	else if (keystroke == KEY_E)
		(img->julia_coef).x += 0.02;
	else if (keystroke == KEY_D)
		(img->julia_coef).x -= 0.02;
	else if (keystroke == KEY_R)
		(img->julia_coef).y += 0.02;
	else if (keystroke == KEY_F)
		(img->julia_coef).y -= 0.02;
	else if (keystroke == KEY_Z)
	{
		if (img->f == mandelbrot)
			img->f = carpette;
		else if (img->f == carpette)
			img->f = julia;
		else
			img->f = mandelbrot;
	}
}

int	manage_keystroke(int keystroke, void *param)
{
	t_image	*img;

printf("keystroke %d\n", keystroke);	
	img = (t_image *)param;
	if (keystroke == KEY_ESC)
	{
		mlx_destroy_window(img->mlx_ptr, img->win_ptr);
		exit(0);
	}
	if (keystroke == KEY_RIGHT || keystroke >= KEY_LEFT || keystroke == KEY_UP || keystroke >= KEY_DOWN)
		moving(img, img->f, keystroke);
	else if (keystroke == KEY_IN)
		zoom_in(img, img->f, img->win_center.x, img->win_center.y);
	else if (keystroke == KEY_OUT)
		zoom_out(img, img->f, img->win_center.x, img->win_center.y);
	else if (keystroke == KEY_A && img->quality > 0)
			(img->quality)--;
	else
		foret_de_ifs(img, keystroke);
	img->f(img);
	mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img_ptr, 0, 0);
	return (keystroke);
}

int	manage_mouse(int button, int x, int y, void *param)
{
	t_image	*img;

	img = (t_image *)param;
	if (button == ON_MOUSEUP)
		zoom_in(img, img->f, x, y);
	if (button == ON_MOUSEDOWN)
		zoom_out(img, img->f, x, y);
	if (button == ON_MOUSEDOWN)
		zoom_out(img, img->f, x, y);
	if (button == CLIC)
		recentrer(img, x, y);
	mlx_put_image_to_window(img->mlx_ptr, img->win_ptr, img->img_ptr, 0, 0);
	return (button);
}

int	manage_expose(int keystroke, void *param)
{
	t_image	*img;

printf("keystroke %d\n", keystroke);	
	img = (t_image *)param;
	if (keystroke == EXPOSE_X)
	{
		mlx_destroy_window(img->mlx_ptr, img->win_ptr);
		exit(0);
	}
	return (keystroke);
}

int	quit(t_image *img)
{
	exit(0);
}

