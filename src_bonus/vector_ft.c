/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_ft.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:24:29 by supersko          #+#    #+#             */
/*   Updated: 2023/01/04 16:39:40 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub3d_bonus.h"

double	distance_point_to_vector(t_point point, t_point v_p1, t_point v_p2)
{
	double	distance;
	double	calc1;
	double	calc2;

	calc1 = abs((v_p2.x - v_p1.x) * (v_p1.y - point.y) - \
			(v_p1.x - point.x) * (v_p2.y - v_p1.y));
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
	numerateur = fabs((line[1].x - line[0].x) * (line[0].y - p_cpy.y) \
			- (line[0].x - p_cpy.x) * (line[1].y - line[0].y));
	denoninateur = sqrt(pow((line[1].x - line[0].x), 2) + \
			pow((line[1].y - line[0].y), 2));
	dist = numerateur / denoninateur;
	return (dist);
}

double	distance_points(t_point p1, t_point p2)
{
	double	dist;

	dist = sqrt(pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2));
	return (dist);
}
