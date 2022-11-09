/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_ft.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:24:29 by supersko          #+#    #+#             */
/*   Updated: 2022/11/07 17:31:07 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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

t_point	translate_pt(t_vector vector, t_point *pt)
{
	if (vector.x > 0)
		pt->x += (int)(vector.x + 0.5);
	else
		pt->x += (int)(vector.x - 0.5);
	if (vector.y > 0)
		pt->y += (int)(vector.y + 0.5);
	else
		pt->y += (int)(vector.y - 0.5);
	return (*pt);
}

void	translate_vector_as_pt(t_vector vector, t_vector *pt)
{
	pt->x += vector.x;
	pt->y += vector.y;
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

/*
  ------> x
 |
 |   /!\ le sens du cercle trigo est inverse aussi
 |
\/
y
*/

void	rotate_vector(t_vector *vector, double radian_angle)
{
	t_vector vector_cpy;

	radian_angle *= -1.0;
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

t_vector	convert_pt_to_vec(t_point p)
{
	t_vector	v;

	v.x = (double)p.x;
	v.y = (double)p.y;
	return (v);
}

double	vector_dot_product(t_vector v1, t_vector v2)
{
	double	dot_product;

	dot_product = v1.x * v2.x + v1.y * v2.y;
	return (dot_product);
}

/* https://www.cuemath.com/geometry/angle-between-vectors/ */
/* sin(a) = |v1 * v2| / (|v1| * |v2|)
				|->cross product
*/
double	vectors_angle_sin(t_vector v1, t_vector v2)
{
	double	sin_angle;

	sin_angle = fabs(vector_dot_product(v1, v2)) / (vec_len(v1) * vec_len(v2));
	return (sin_angle);
}
