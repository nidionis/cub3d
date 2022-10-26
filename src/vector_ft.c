/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_ft.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:24:29 by supersko          #+#    #+#             */
/*   Updated: 2022/10/26 19:35:53 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_point	get_vector(t_point *from, t_point *to)
{
	t_point	vector;

	vector.x = to->x - from->x;
	vector.y = -1 * (to->y - from->y);
	return (vector);
}

t_point	vec_diff(t_point v1, t_point v2)
{
	t_point	diff_vec;

	diff_vec.x = v1.x - v2.x;
	diff_vec.y = v1.y - v2.y;
	return (diff_vec);
}

t_point	vec_scale(t_point vector, double scale)
{
	vector.x = (int)(scale * (double)vector.x);
	vector.y = (int)(scale * (double)vector.y);
	return (vector);
}

void	add_vec(t_point	*pt, t_point vector)
{
	pt->x += vector.x;
	pt->y += vector.y;
}

void	translate_pt(t_vector vector, t_point *pt)
{
	pt->x += vector.x;
	pt->y += vector.y;
}
