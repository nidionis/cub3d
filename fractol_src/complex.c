/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:24:29 by supersko          #+#    #+#             */
/*   Updated: 2022/05/30 17:41:27 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

t_pt	complex_square(t_pt complex_nb)
{
	t_pt	sq_nb;

	sq_nb.x = pow(complex_nb.x, 2) - pow(complex_nb.y, 2);
	sq_nb.y = 2 * complex_nb.x * complex_nb.y;
	return (sq_nb);
}

t_pix	convert_pt_to_pix(t_imgg *img, t_pt pt, t_pix center)
{
	t_pix	pix;

	pix.x = (int)(pt.x * (double)img->scale[0]) + center.x;
	pix.y = (int)(pt.y * (double)img->scale[1]) + center.y;
	return (pix);
}

t_pt	convert_pix_to_pt(t_imgg *img, t_pix pix, t_pix center)
{
	t_pt	pt;

	pt.x = (double)(pix.x - center.x) / (double)img->scale[0];
	pt.y = (double)(pix.y - center.y) / (double)img->scale[1];
	return (pt);
}
