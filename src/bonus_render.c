/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:17:56 by suplayerko        #+#    #+#             */
/*   Updated: 2023/01/04 17:41:48 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/* draw one texture line */
void	draw_obstacle_texture(t_data *data, t_point pts[2], int \
line_height, t_obstacle *obstacle)
{
	double			ratio[2];
	t_point			text_pix;
	unsigned int	color;
	t_img_data		*t;

	t = obstacle->texture;
	ratio[_x] = obstacle->texture_x / (double) UNITS_PER_BOX;
	text_pix.x = t->line_len * ratio[_x] / (double)(t->bpp / 8);
	if (pts[0].y < 0)
		pts[0].y = 0;
	while (pts[0].y <= pts[1].y && pts[0].y < data->window->height)
	{
		ratio[_y] = 1.0 - (double)(pts[1].y - pts[0].y) / (double)line_height;
		text_pix.y = t->line_height * ratio[_y];
		color = get_texture_pix(t, text_pix);
		my_mlx_pixel_put(data->img, pts[0].x, pts[0].y, color);
		pts[0].y++;
	}
}

void	draw_obstacles(t_data *data, t_point pts[2]
	, t_list *l_obstacles)
{
	t_list		*tmp;
	t_obstacle	*obstacle;
	int			line_height;

	tmp = l_obstacles;
	while (tmp)
	{
		obstacle = (t_obstacle *)tmp->content;
		inityvar(&pts[0], &pts[1], &line_height, obstacle->dist);
		draw_obstacle_texture(data, pts, line_height, obstacle);
		tmp = tmp->next;
	}
	ft_lstclear(&l_obstacles, free);
}

/* draw a large line in camera definition is low */
void	draw_wall_textured(t_data *data, int i_ray)
{
	t_rayponse	ray;
	int			line_height;
	t_point		pts[2];
	int			line_width;

	ray = data->cam->array[i_ray];
	initxvar(&pts[0], &pts[1], &line_width, i_ray);
	inityvar(&pts[0], &pts[1], &line_height, ray.dist_from_plan);
	while (line_width--)
	{
		draw_texture(data, pts, line_height, &ray);
		draw_obstacles(data, pts, ray.obstacles_ls);
		pts[0].x++;
		pts[1].x++;
	}
	ft_lstclear(&ray.obstacles_ls, free);
}
