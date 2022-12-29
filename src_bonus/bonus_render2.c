/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_render2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 18:30:30 by dpaulino          #+#    #+#             */
/*   Updated: 2022/12/29 13:59:16 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/cub3d.h"

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
	int	height;

	height = get_res_height();
	if (distance <= 1)
		distance = 1;
	if (distance < 0)
		distance = 2147483647;
	*line_height = (int)LINE_HEIGHT / distance;
	start->y = (int)height / 2 - *line_height / 2;
	end->y = (int)height / 2 + *line_height / 2;
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
	int				height;

	height = get_res_height();
	t = data->wall_textures[ray->side];
	ratio[_x] = get_wallx(ray) / (double) UNITS_PER_BOX;
	text_pix.x = t->line_len * ratio[_x] / (double)(t->bpp / 8);
	if (pts[0].y < 0)
		pts[0].y = 0;
	while (pts[0].y <= pts[1].y && pts[0].y < height)
	{
		ratio[_y] = 1.0 - (double)(pts[1].y - pts[0].y) / (double)line_height;
		text_pix.y = t->line_height * ratio[_y];
		color = get_texture_pix(t, text_pix);
		my_mlx_pixel_put(data->img, pts[0].x, pts[0].y, color);
		pts[0].y++;
	}
}
