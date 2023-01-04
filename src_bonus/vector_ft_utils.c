/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_ft_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 16:39:03 by dpaulino          #+#    #+#             */
/*   Updated: 2023/01/04 16:39:57 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub3d_bonus.h"

double	vec_len(t_vector vector)
{
	double	len;
	double	x_square;
	double	y_square;

	x_square = vector.x * vector.x;
	y_square = vector.y * vector.y;
	len = sqrt(x_square + y_square);
	return (len);
}

t_point	make_point(int x, int y)
{
	t_point	p;

	p.x = x;
	p.y = y;
	return (p);
}

t_vector	vec_scale(t_vector vector, double scale)
{
	vector.x = (scale * vector.x);
	vector.y = (scale * vector.y);
	return (vector);
}

t_point	translate_pt(t_vector vector, t_point pt)
{
	if (vector.x > 0)
		pt.x += (int)(vector.x + 0.50001);
	else
		pt.x += (int)(vector.x - 0.50001);
	if (vector.y > 0)
		pt.y += (int)(vector.y + 0.50001);
	else
		pt.y += (int)(vector.y - 0.50001);
	return (pt);
}

t_point	translate_pt_inplace(t_vector vector, t_point *pt)
{
	if (vector.x > 0)
		pt->x += (int)(vector.x + 0.50001);
	else
		pt->x += (int)(vector.x - 0.50001);
	if (vector.y > 0)
		pt->y += (int)(vector.y + 0.50001);
	else
		pt->y += (int)(vector.y - 0.50001);
	return (*pt);
}
