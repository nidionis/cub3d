/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:24:29 by supersko          #+#    #+#             */
/*   Updated: 2022/10/26 16:50:36 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

static unsigned int	mandel_pix_color(t_vector pt_parser, t_image *img)
{
	int		n;
	t_vector	zn;
	double	tmp;
	int		color_octet;

	zn.x = 0;
	zn.y = 0;
	n = 0;
	while (n++ < img->quality && pow(zn.x, 2) + pow(zn.y, 2) < 4)
	{
		tmp = zn.x;
		zn.x = pow(zn.x, 2) - pow(zn.y, 2) + pt_parser.x;
		zn.y = 2 * tmp * zn.y + pt_parser.y;
	}
	color_octet = n * 255 / img->quality;
	if (n != img->quality)
		return (color_render(n * 255.0 / img->quality, img));
	return (0);
}

void	mandelbrot(t_image *img)
{
	t_point	parser;
	t_vector	pt_parser;

	parser.x = 0;
	parser.y = 0;
	while (parser.y < (int)img->size[1] && parser.x < (int)img->size[0])
	{
		pt_parser = convert_point_to_pt(img, parser, img->center);
		put_point(img, parser, mandel_pix_color(pt_parser, img));
		(parser.x)++;
		if (parser.x == (int)img->size[0])
		{
			parser.x = 0;
			(parser.y)++;
		}
	}
}

unsigned int	is_white(int n)
{
	if (n % 3 == 1)
		return (1);
	else if (n > 3)
		return (is_white(n / 3));
	else
		return (0);
}

void	carpette(t_image *img)
{
	t_point	parser;

	parser.x = 0;
	parser.y = 0;
	while (parser.y < (int)img->size[1] && (int)img->size[0] > parser.x)
	{
		if (!(is_white(parser.x) || is_white(parser.y)))
			put_point(img, parser, color_render(255, img));
		else
			put_point(img, parser, 0);
		(parser.x)++;
		if (parser.x == (int)img->size[0])
		{
			parser.x = 0;
			(parser.y)++;
		}
	}
}
