/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_keypad.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:24:29 by supersko          #+#    #+#             */
/*   Updated: 2022/10/26 15:28:41 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

t_image	*zoom_in(t_image *img, void (*f)(), int x, int y)
{
	double	ratio;
	t_pix	mouse_pix;
	t_pix	mouse_to_center;

	ratio = 1.1;
	mouse_pix = make_pix_pt(x, y);
	mouse_to_center = get_vector(&mouse_pix, &(img->win_center));
	apply_vec(&(img->center), mouse_to_center);
	img->scale[0] *= ratio;
	img->scale[1] *= ratio;
	f(img);
	return (img);
}

t_image	*zoom_out(t_image *img, void (*f)(), int x, int y)
{
	double	ratio;
	t_pix	mouse_pix;
	t_pix	mouse_to_center;
	t_pix	mouse_to_cent_scaled;

	ratio = 1.1;
	mouse_pix = make_pix_pt(x, y);
	mouse_to_center = get_vector(&(img->win_center), &mouse_pix);
	mouse_to_cent_scaled = vec_scale(mouse_to_center, ratio);
	apply_vec(&(img->center), vec_scale(mouse_to_center, ratio / 2.0));
	img->scale[0] /= ratio;
	img->scale[1] /= ratio;
	f(img);
	return (img);
}

void	moving(t_image *img, void (*f)(), int keystroke)
{
	int	step_size;

	step_size = img->size[0] / 30;
	if (keystroke == KEY_LEFT)
		img->center.x += step_size;
	else if (keystroke == KEY_RIGHT)
		img->center.x -= step_size;
	else if (keystroke == KEY_DOWN)
		img->center.y -= step_size;
	else if (keystroke == KEY_UP)
		img->center.y += step_size;
	f(img);
}

void	recentrer(t_image *img, int x, int y)
{
	t_pix	pix_clic;
	t_pix	vector;

	pix_clic = make_pix_pt(x, y);
	vector.x = (img->win_center).x - pix_clic.x;
	vector.y = (img->win_center).y - pix_clic.y;
	apply_vec(&(img->center), vector);
	(img->f)(img);
}
