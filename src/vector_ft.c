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

// C++ program to find modulo of floating
// point numbers.

double float_modulo(double a, double b)
{
	double mod;

	if (a < 0)
		mod = -a;
	else
		mod = a;
	if (b < 0)
		b = -b;
	while (mod >= b)
		mod = mod - b;
	if (a < 0)
		return -mod;
	return mod;
}

t_point	make_point(int x, int y)
{
	t_point	p;

	p.x = x;
	p.y = y;
	return (p);
}

t_point	get_vector(t_point *from, t_point *to)
{
	t_point	vector;

	vector.x = to->x - from->x;
	vector.y = -1 * (to->y - from->y);
	return (vector);
}

t_vector	vec_scale(t_vector vector, double scale)
{
	vector.x = (scale * vector.x);
	vector.y = (scale * vector.y);
	return (vector);
}

void	add_vec(t_point	*pt, t_point vector)
{
	pt->x += vector.x;
	pt->y += vector.y;
}

void	translate_pt(t_vector vector, t_point *pt)
{
	pt->x += (int)vector.x;
	pt->y += (int)vector.y;
}

double	degree_to_radian(double degree_angle)
{
	double	rad_angle;

	/*
	if (degree_angle < 0 || degree_angle > 360)
		degree_angle = float_modulo(degree_angle, 360);
		*/
	rad_angle = ((double)PI * degree_angle / (double)180.0) ;
	return (rad_angle);
}

void	rotate_vector(t_vector *vector, double radian_angle)
{
	t_vector vector_cpy;

	vector_cpy = *vector;
	vector->x = vector->x * cos(radian_angle) - vector->y * sin(radian_angle);
	vector->y = vector->y * cos(radian_angle) + vector_cpy.x * sin(radian_angle);
}

/* https://en.wikipedia.org/wiki/Distance_from_a_point_to_a_line */
double	distance_point_to_vector(t_point point, t_point v_p1, t_point v_p2)
{
	double	distance;
	double	calc1;
	double	calc2;

	calc1 = abs((v_p2.x - v_p1.x) * (v_p1.y - point.y) - (v_p1.x - point.x) * (v_p2.y - v_p1.y));
	calc2 = sqrt(pow(v_p2.x - v_p1.x, 2) + pow(v_p2.y - v_p1.y, 2));
	distance = calc1 / calc2;
	return (distance);
}
