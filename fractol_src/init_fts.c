/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:24:29 by supersko          #+#    #+#             */
/*   Updated: 2022/10/26 16:50:36 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

void	img_default_init(t_image	*img)
{
	img->bpp = sizeof(int);
	img->endian = 0;
	img->size[0] = 800;
	img->size[1] = 800;
	img->line_len = img->size[0] + 1;
	img->scale[0] = img->size[0] / 5;
	img->scale[1] = img->size[1] / 5;
	(img->center).x = img->size[0] / 2;
	(img->center).y = img->size[1] / 2;
	img->color_shift = 0;
	img->quality = 10;
	img->julia_coef.x = 0.28;
	img->julia_coef.y = 0.008;
}

void	set_win_center(t_image *img)
{
	(img->win_center).x = img->size[0] / 2;
	(img->win_center).y = img->size[1] / 2;
}

t_point	make_pix_pt(int x, int y)
{
	t_point	pix_pt;

	pix_pt.x = x;
	pix_pt.y = y;
	return (pix_pt);
}
