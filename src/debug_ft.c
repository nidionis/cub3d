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

unsigned int	get_texture_pix(t_img_data *t, t_point pix)
{
	int addr;
	unsigned int color;

	addr = pix.y * t->line_len + pix.x * (t->bpp / 8);
	color = (unsigned int)(*(int *)(t->adress + addr));
	return (color);
}

int	get_wallX(t_rayponse *ray)
{
	int	Xhit;

	if (ray->side == NO || ray->side == SO)
		Xhit = ray->hit_point.x % (int) UNITS_PER_BOX;
	else
		Xhit = ray->hit_point.y % (int) UNITS_PER_BOX;
	return (Xhit);
}

void	draw_texture(t_data *data, t_point start, t_point end, int line_height, t_rayponse *ray)
{
	double		ratio[2];
	t_point		text_pix;
	unsigned int		color;
	t_img_data	t;

	t = data->wall_textures[ray->side];
	ratio[_x] = get_wallX(ray) / (double) UNITS_PER_BOX;
	text_pix.x = t.line_len * ratio[_x] / (double)(t.bpp / 8);
	if (start.y < 0)
		start.y = 0;
	while (start.y <= end.y && start.y < SCREEN_HEIGHT)
	{
		ratio[_y] = 1.0 - (double)(end.y - start.y) / (double)line_height;
		text_pix.y = t.line_height * ratio[_y];
		color = get_texture_pix(&t, text_pix);
		my_mlx_pixel_put(data->img, start.x, start.y, color);
		start.y++;
	}
}

void	init_vars2(t_point *start, t_point *end, int *line_height, t_rayponse *ray)
{
	*line_height = (int)LINE_HEIGHT / ray->dist_from_plan;
	start->y = (int)SCREEN_HEIGHT / 2 - *line_height / 2;
	end->y = (int)SCREEN_HEIGHT / 2 + *line_height / 2;
}

void   init_vars(t_point *start, t_point *end, int *line_width, int i_ray)
{
       *line_width = LINE_WIDTH;
       if (*line_width <= 0)
               *line_width = 1;
       start->x = i_ray * (*line_width);
       end->x = i_ray * (*line_width);
}

void	draw_wall_textured(t_data *data, int i_ray)
{
	t_rayponse	ray;
	int line_height;
	t_point		start;
	t_point		end;
	int	line_width;

	ray = data->cam->arRay[i_ray];
	init_vars(&start, &end, &line_width, i_ray);
	init_vars2(&start, &end, &line_height, &ray);
	while (line_width--)
	{
		draw_texture(data, start, end, line_height, &ray);
		start.x++;
		end.x++;
	}
}

/*
void	draw_wall_line(t_data *data, int i)
{
	t_point	start;
	t_point	ceiling_start;
	t_point	floor_end;
	t_point	end;
	t_point colors;
	t_rayponse	ray;
	colors.x = 0;
	colors.y = 0;
	int		line_height;
	int		color;
	int		line_width = SCREEN_WIDTH / CAM_QUALITY;
	int		loop;
	double	LINE_HEIGHT;
	(void)color;
	ray = data->cam->arRay[i];
	good_ratio = (double)SCREEN_HEIGHT * (double)UNITS_PER_BOX;
	start.x = i * line_width;
	end.x = i * line_width;
	floor_end.x = i * line_width;
	floor_end.y = SCREEN_HEIGHT - 1;
	ceiling_start.x = i * line_width;
	ceiling_start.y = 0;
	line_height = good_ratio / ray.dist_from_plan;
	if (line_height > SCREEN_HEIGHT)
		line_height = (int)SCREEN_HEIGHT;
	start.y = (int)SCREEN_HEIGHT / 2 - line_height / 2;
	end.y = (int)SCREEN_HEIGHT / 2 + line_height / 2;
	if (ray.side == NORTH)
		color = rgb_conv(100, 0, 255);
	else if (ray.side == SOUTH)
		color = rgb_conv(100, 255, 255);
	else if (ray.side == EAST)
		color = rgb_conv(0, 255, 0);
	else if (ray.side == WEST)
		color = rgb_conv(255, 0, 0);
	else
		color = rgb_conv(20, 20, 20);
	loop = 0;
	while (loop < line_width)
	{
		(void)colors;
		draw_line(data, &ceiling_start, &start, data->image->ceiling_color);
		// draw_line(data, &start, &end, color);
		//draw_textures(data, &start, &end, colors);
		draw_line(data, &end, &floor_end, data->image->floor_color);
		start.x++;
		end.x++;
		floor_end.x++;
		ceiling_start.x++;
		loop++;
	}
}

*/
/*
void	draw_obstacle(t_data *data, int i)
{
	t_point	start;
	t_point	end;
	t_rayturned	ray;
	int		line_height;
	int		color;
	int		line_width = SCREEN_WIDTH / CAM_QUALITY;
	int		loop;
	double	good_ratio;
	t_obstacle	*obstacle_ls;
	
	ray = data->cam->arRay[i];
	good_ratio = (double)SCREEN_HEIGHT * (double)UNITS_PER_BOX;
	start.x = i * line_width;
	end.x = i * line_width;
	line_height = good_ratio / ray.dist_from_plan;
	if (line_height > SCREEN_HEIGHT / 2)
		line_height = (int)SCREEN_HEIGHT / 2;
	start.y = (int)SCREEN_HEIGHT / 2 - line_height / 2;
	end.y = (int)SCREEN_HEIGHT / 2 + line_height / 2;
	color = rgb_conv(60, 90, 10);
	loop = 0;
	while (loop < line_width)
	{
		draw_line(data, &start, &end, color);
		start.x++;
		end.x++;
		loop++;
	}
}
*/
