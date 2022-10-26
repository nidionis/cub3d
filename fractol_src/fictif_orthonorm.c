/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fictif_orthonorm.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:24:29 by supersko          #+#    #+#             */
/*   Updated: 2022/10/26 16:50:36 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

void	orthonorm_rel(t_image *img)
{
	t_point	parser;
	t_vector	pt_parser;

	parser.x = 0;
	parser.y = 0;
	while (parser.y < (int)img->size[1] && parser.x <= (int)img->size[0])
	{
		if (parser.x == (int)img->size[0])
		{
			parser.x = 0;
			(parser.y)++;
		}
		pt_parser = convert_point_to_pt(img, parser, img->center);
		if ((int)pt_parser.x == pt_parser.x || (int)pt_parser.y == pt_parser.y)
			put_point(img, parser, rgb_conv(100, 255, 0));
		else if (parser.y < (int)img->size[1])
			put_point(img, parser, 0);
		(parser.x)++;
	}
	circle(img, 5, img->center, rgb_conv(255, 0, 0));
}
