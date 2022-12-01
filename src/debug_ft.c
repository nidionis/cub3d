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
	double	good_ratio;
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
