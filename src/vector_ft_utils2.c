/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_ft_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 16:39:12 by dpaulino          #+#    #+#             */
/*   Updated: 2023/01/04 17:45:40 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	translate_vector_as_pt(t_vector vector, t_vector *pt)
{
	pt->x += vector.x;
	pt->y += vector.y;
}

double	degree_to_radian(double degree_angle)
{
	double	rad_angle;

	rad_angle = ((double)PI * degree_angle / (double)180.0);
	return (rad_angle);
}

void	rotate_vector(t_vector *vector, double radian_angle)
{
	t_vector	vector_cpy;
	double		two_pi;

	two_pi = 2.0 * (double)PI;
	while (radian_angle < 0)
		radian_angle += two_pi;
	while (radian_angle > two_pi)
		radian_angle -= two_pi;
	vector_cpy = *vector;
	vector->x = vector_cpy.x * cos(radian_angle) - \
				vector_cpy.y * sin(radian_angle);
	vector->y = vector_cpy.y * cos(radian_angle) + \
				vector_cpy.x * sin(radian_angle);
}
