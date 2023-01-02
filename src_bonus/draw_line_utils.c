/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:32:07 by dpaulino          #+#    #+#             */
/*   Updated: 2023/01/02 12:54:25 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub3d_bonus.h"

void	my_mlx_pixel_put(t_img_data *img, int x, int y, unsigned int color)
{
	int	*dst;
	int	width;

	width = 0;
	if (g_status == 0)
		width = SCREEN_WIDTH;
	else if (g_status == 1)
		width = 1900;
	else if (g_status == 2)
		width = 1200;
	else if (g_status == 3)
		width = 700;
	dst = img->address + (y * width + x);
	*(unsigned int *)dst = color;
}

void	init_line_values(t_line *line, t_point	*start, t_point	*end)
{
	line->dx = end->x - start->x;
	line->dy = end->y - start->y;
	line->dx1 = abs(line->dx);
	line->dy1 = abs(line->dy);
	line->px = 2 * line->dy1 - line->dx1;
	line->py = 2 * line->dx1 - line->dy1;
}
