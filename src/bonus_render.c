/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_ft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suplayerko <suplayerko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:17:56 by suplayerko          #+#    #+#             */
/*   Updated: 2022/12/01 17:19:27 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* return the color in a texture from a pixel point */
unsigned int	get_texture_pix(t_img_data *t, t_point pix)
{
	int				addr;
	unsigned int	color;

	addr = pix.y * t->width + pix.x;
	color = t->address[addr];
	return (color);
}

/* return the position of the ray in the wall (in UNIT_PER_BOX) */
int	get_wallx(t_rayponse *ray)
{
	int	x_hit;

	if (ray->side == NO || ray->side == SO)
		x_hit = ray->hit_point.x % (int) UNITS_PER_BOX;
	else
		x_hit = ray->hit_point.y % (int) UNITS_PER_BOX;
	return (x_hit);
}

void	inityvar(t_point *start, t_point *end, int *line_height, int distance)
{
	if (distance <= 1)
		distance = 1;
	if (distance < 0)
		distance = 2147483647;
	*line_height = (int)LINE_HEIGHT / distance;
	start->y = (int)SCREEN_HEIGHT / 2 - *line_height / 2;
	end->y = (int)SCREEN_HEIGHT / 2 + *line_height / 2;
}

void	initxvar(t_point *start, t_point *end, int *line_width, int i_ray)
{
	*line_width = LINE_WIDTH;
	if (*line_width <= 0)
		*line_width = 1;
	start->x = i_ray * (*line_width);
	end->x = i_ray * (*line_width);
}

/* draw one texture line */
void	draw_texture(t_data *data, t_point pts[2], \
int line_height, t_rayponse *ray)
{
	double			ratio[2];
	t_point			text_pix;
	unsigned int	color;
	t_img_data		*t;

	t = data->wall_textures[ray->side];
	ratio[_x] = get_wallx(ray) / (double) UNITS_PER_BOX;
	text_pix.x = t->line_len * ratio[_x] / (double)(t->bpp / 8);
	if (pts[0].y < 0)
		pts[0].y = 0;
	while (pts[0].y <= pts[1].y && pts[0].y < SCREEN_HEIGHT)
	{
		ratio[_y] = 1.0 - (double)(pts[1].y - pts[0].y) / (double)line_height;
		text_pix.y = t->line_height * ratio[_y];
		color = get_texture_pix(t, text_pix);
		my_mlx_pixel_put(data->img, pts[0].x, pts[0].y, color);
		pts[0].y++;
	}
}

/* draw one texture line */
void	draw_obstacle_texture(t_data *data, t_point pts[2], int \
line_height, t_obstacle *obstacle)
{
	double			ratio[2];
	t_point			text_pix;
	unsigned int	color;
	t_img_data		*t;

	t = obstacle->texture;
	ratio[_x] = obstacle->textureX / (double) UNITS_PER_BOX;
	text_pix.x = t->line_len * ratio[_x] / (double)(t->bpp / 8);
	if (pts[0].y < 0)
		pts[0].y = 0;
	while (pts[0].y <= pts[1].y && pts[0].y < SCREEN_HEIGHT)
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
