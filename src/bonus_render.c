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
	int addr;
	unsigned int color;
	addr = pix.y * t->width + pix.x;

	color = t->address[addr];
	return (color);
}

/* return the position of the ray in the wall (in UNIT_PER_BOX) */
int	get_wallX(t_rayponse *ray)
{
	int	Xhit;

	if (ray->side == NO || ray->side == SO)
		Xhit = ray->hit_point.x % (int) UNITS_PER_BOX;
	else
		Xhit = ray->hit_point.y % (int) UNITS_PER_BOX;
	return (Xhit);
}

/* draw one texture line */
void	draw_texture(t_data *data, t_point start, t_point end, int line_height, t_rayponse *ray)
{
	double		ratio[2];
	t_point		text_pix;
	unsigned int		color;
	t_img_data	*t;
(void)color;
(void) text_pix;
	t = data->wall_textures[ray->side];
	ratio[_x] = get_wallX(ray) / (double) UNITS_PER_BOX;
	text_pix.x = t->line_len * ratio[_x] / (double)(t->bpp / 8);
	if (start.y < 0)
		start.y = 0;
	while (start.y <= end.y && start.y < SCREEN_HEIGHT)
	{
		ratio[_y] = 1.0 - (double)(end.y - start.y) / (double)line_height;
		text_pix.y = t->line_height * ratio[_y];
		color = get_texture_pix(t, text_pix);
		my_mlx_pixel_put(data->img, start.x, start.y, color);
		start.y++;
	}
}

void	init_Yvar(t_point *start, t_point *end, int *line_height, int distance)
{
	if (distance == 0)
		distance = 1;
	if (distance < 0)
		distance = 2147483647;
	*line_height = (int)LINE_HEIGHT / distance;
	start->y = (int)SCREEN_HEIGHT / 2 - *line_height / 2;
	end->y = (int)SCREEN_HEIGHT / 2 + *line_height / 2;
}

void   init_Xvar(t_point *start, t_point *end, int *line_width, int i_ray)
{
       *line_width = LINE_WIDTH;
       if (*line_width <= 0)
               *line_width = 1;
       start->x = i_ray * (*line_width);
       end->x = i_ray * (*line_width);
}


/* draw one texture line */
void	draw_obstacle_texture(t_data *data, t_point start, t_point end, int line_height, t_obstacle *obstacle)
{
	double		ratio[2];
	t_point		text_pix;
	unsigned int		color;
	t_img_data	*t;

	t = obstacle->texture;
	ratio[_x] = obstacle->textureX / (double) UNITS_PER_BOX;
	text_pix.x = t->line_len * ratio[_x] / (double)(t->bpp / 8);
	if (start.y < 0)
		start.y = 0;
	while (start.y <= end.y && start.y < SCREEN_HEIGHT)
	{
		ratio[_y] = 1.0 - (double)(end.y - start.y) / (double)line_height;
		text_pix.y = t->line_height * ratio[_y];
		color = get_texture_pix(t, text_pix);
		my_mlx_pixel_put(data->img, start.x, start.y, color);
		start.y++;
	}
}

void	draw_obstacles(t_data *data, t_point *start, t_point *end, t_list *l_obstacles)
{
	t_list 		*tmp;
	t_obstacle 	*obstacle;
	int		line_height;

	tmp = l_obstacles;
	while (tmp)
	{
		obstacle = (t_obstacle *)tmp->content;
		init_Yvar(start, end, &line_height, obstacle->dist);
		draw_obstacle_texture(data, *start, *end, line_height, obstacle);
		tmp = tmp->next;
	}
}

/* draw a large line in camera definition is low */ 
void	draw_wall_textured(t_data *data, int i_ray)
{
	t_rayponse	ray;
	int line_height;
	t_point		start;
	t_point		end;
	int	line_width;

	ray = data->cam->arRay[i_ray];
	init_Xvar(&start, &end, &line_width, i_ray);
	init_Yvar(&start, &end, &line_height, ray.dist_from_plan);
	while (line_width--)
	{
		draw_texture(data, start, end, line_height, &ray);
		draw_obstacles(data, &start, &end, ray.obstacles_ls);
		start.x++;
		end.x++;
	}
	ft_lstclear(&ray.obstacles_ls, free);
}
