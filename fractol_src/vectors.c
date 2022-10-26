/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:24:29 by supersko          #+#    #+#             */
/*   Updated: 2022/10/26 15:28:41 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

t_pix	get_vector(t_pix *from, t_pix *to)
{
	t_pix	vector;

	vector.x = to->x - from->x;
	vector.y = -1 * (to->y - from->y);
	return (vector);
}

t_pix	vec_diff(t_pix v1, t_pix v2)
{
	t_pix	diff_vec;

	diff_vec.x = v1.x - v2.x;
	diff_vec.y = v1.y - v2.y;
	return (diff_vec);
}

t_pix	vec_scale(t_pix vector, double scale)
{
	vector.x = (int)(scale * (double)vector.x);
	vector.y = (int)(scale * (double)vector.y);
	return (vector);
}

void	add_vec(t_pix	*pt, t_pix vector)
{
	pt->x += vector.x;
	pt->y += vector.y;
}
