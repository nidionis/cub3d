/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:24:29 by supersko          #+#    #+#             */
/*   Updated: 2022/10/26 16:51:14 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

t_vector	complex_square(t_vector complex_nb)
{
	t_vector	sq_nb;

	sq_nb.x = pow(complex_nb.x, 2) - pow(complex_nb.y, 2);
	sq_nb.y = 2 * complex_nb.x * complex_nb.y;
	return (sq_nb);
}

t_point	convert_point_to_pix(t_image *img, t_vector pt, t_point center)
{
	t_point	pix;

	pix.x = (int)(pt.x * (double)img->scale[0]) + center.x;
	pix.y = (int)(pt.y * (double)img->scale[1]) + center.y;
	return (pix);
}

t_vector	convert_point_to_pt(t_image *img, t_point pix, t_point center)
{
	t_vector	pt;

	pt.x = (double)(pix.x - center.x) / (double)img->scale[0];
	pt.y = (double)(pix.y - center.y) / (double)img->scale[1];
	return (pt);
}
