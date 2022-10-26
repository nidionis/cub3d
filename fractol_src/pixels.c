/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:24:29 by supersko          #+#    #+#             */
/*   Updated: 2022/10/26 15:24:41 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

unsigned int	get_offset(t_pix pix, t_image *img)
{
	return (pix.y * img->line_len + pix.x * (img->bpp / 8));
}

void	put_pix(t_image *img, t_pix pix, int color)
{
	void	*dst;

	dst = img->addr + get_offset(pix, img);
	*(unsigned int *)dst = color;
}

unsigned int	rgb_conv(int R, int G, int B)
{
	return ((unsigned int) R * 65536 + (unsigned int) G * 256 + B);
}

unsigned int	color_render(unsigned int color_byte, t_image *img)
{
	if (img->color_shift % 6 == 0)
		color_byte = rgb_conv(color_byte, 0, 0);
	else if (img->color_shift % 6 == 1)
		color_byte = rgb_conv(color_byte, color_byte, 0);
	else if (img->color_shift % 6 == 2)
		color_byte = rgb_conv(0, color_byte, 0);
	else if (img->color_shift % 6 == 3)
		color_byte = rgb_conv(0, color_byte, color_byte);
	else if (img->color_shift % 6 == 4)
		color_byte = rgb_conv(0, 0, color_byte);
	else if (img->color_shift % 6 == 5)
		color_byte = rgb_conv(color_byte, 0, color_byte);
	return (color_byte);
}
