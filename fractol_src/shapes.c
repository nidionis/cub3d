/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:24:29 by supersko          #+#    #+#             */
/*   Updated: 2022/05/31 15:05:27 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

int	pix_dst(t_pix p1, t_pix p2)
{
	int	dst;

	dst = (int) sqrt(pow((int)p1.x - (int)p2.x, 2) + \
		pow((int)p1.y - (int)p2.y, 2));
	return (dst);
}

int	is_in_win(unsigned int win_size[2], t_pix pix)
{
	if (pix.x > (int)win_size[0] || pix.x < 0 \
		|| pix.y < 0 || pix.y > (int)win_size[1])
	{
		return (0);
	}
	return (1);
}

void	circle(t_imgg *img, int r, t_pix center, unsigned int color)
{
	t_pix	parser;
	t_pix	parser_init;

	parser.x = center.x - r;
	parser.y = center.y - r;
	parser_init = parser;
	while (parser.x <= center.x + r && parser.y <= center.y + r)
	{
		if (parser.x == center.x + r)
		{
			parser.x = parser_init.x;
			(parser.y)++;
		}
		if (is_in_win(img->size, parser) && pix_dst(center, parser) < r)
			put_pix(img, parser, color);
		(parser.x)++;
	}
}
