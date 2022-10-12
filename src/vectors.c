/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:24:29 by supersko          #+#    #+#             */
/*   Updated: 2022/05/31 15:06:16 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_pix	get_vector(t_pix *from, t_pix *to)
{
	t_pix	vec;

	vec.x = to->x - from->x;
	vec.y = -1 * (to->y - from->y);
	return (vec);
}

t_pix	vec_diff(t_pix v1, t_pix v2)
{
	t_pix	diff_vec;

	diff_vec.x = v1.x - v2.x;
	diff_vec.y = v1.y - v2.y;
	return (diff_vec);
}

t_pix	vec_scale(t_pix vec, double scale)
{
	vec.x = (int)(scale * (double)vec.x);
	vec.y = (int)(scale * (double)vec.y);
	return (vec);
}

void	add_vec(t_pix	*pt, t_pix vec)
{
	pt->x += vec.x;
	pt->y += vec.y;
}
