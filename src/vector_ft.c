/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_ft.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:24:29 by supersko          #+#    #+#             */
/*   Updated: 2022/11/11 14:49:33 by supersko         ###   ########.fr       */
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
	t_vector 	vector_cpy;
	double		two_pi;

	two_pi = 2.0 * (double)PI;
	while (radian_angle < 0)
		radian_angle += two_pi;
	while (radian_angle > two_pi)
		radian_angle -= two_pi;
	vector_cpy = *vector;
	vector->x = vector_cpy.x * cos(radian_angle) - vector_cpy.y * sin(radian_angle);
	vector->y = vector_cpy.y * cos(radian_angle) + vector_cpy.x * sin(radian_angle);
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

/* line defined by :
line[0] = origin_point
line[1] = any_other_point
*/
double	distance_line_to_point(t_vector line[2], t_point p)
{
	double		dist;
	double		numerateur;
	double		denoninateur;
	t_vector	p_cpy;

	p_cpy.x = (double)p.x;
	p_cpy.y = (double)p.y;
	numerateur = fabs((line[1].x - line[0].x) * (line[0].y - p_cpy.y) - (line[0].x - p_cpy.x) * (line[1].y - line[0].y));
	denoninateur = sqrt(pow((line[1].x - line[0].x), 2) + pow((line[1].y - line[0].y), 2));
	dist = numerateur / denoninateur;
	return (dist);
}

double	distance_points(t_point p1, t_point p2)
{
	double	dist;

	dist = sqrt(pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2));
	return (dist);
}
