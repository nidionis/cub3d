/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 03:41:47 by dpaulino          #+#    #+#             */
/*   Updated: 2023/01/03 17:10:17 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub3d_bonus.h"

int	load_images(t_data *data, t_img_data *image, char *path)
{
	t_point	size;

	size = get_img_size(path);
	image->width = size.x;
	image->height = size.y;
	image->img = mlx_xpm_file_to_image(data->window->mlx, \
		path, &image->line_len, &image->line_height);
	if (image->img == NULL)
	{
		printf("No image found \n");
		exit(0);
	}
	image->address = (int *)mlx_get_data_addr(image->img, \
		&image->bpp, &image->line_len, &image->endian);
	if (image->address == NULL)
		exit(0);
	return (0);
}

void	alloc_menu(t_data *data)
{
	data->menu = malloc(sizeof(t_menu));
	data->menu->background[BG] = malloc(sizeof(t_img_data));
	data->menu->background[NEW_GAME] = malloc(sizeof(t_img_data));
	data->menu->background[EXIT] = malloc(sizeof(t_img_data));
	data->menu->background[LAYOUT] = malloc(sizeof(t_img_data));
	data->menu->background[LOGO] = malloc(sizeof(t_img_data));
	data->menu->background[CONTROLS] = malloc(sizeof(t_img_data));
	data->menu->background[BACK] = malloc(sizeof(t_img_data));
	data->menu->background[NEW_BG] = malloc(sizeof(t_img_data));
	data->menu->background[EXTRAS] = malloc(sizeof(t_img_data));
	data->menu->background[CONTROLS_KEYS] = malloc(sizeof(t_img_data));
	data->menu->background[10] = malloc(sizeof(t_img_data));
}

void	init_menu_var(t_data *data)
{
	t_menu	*menu;

	menu = data->menu;
	menu->new_game = 1;
	menu->controls = 0;
	menu->extras = 0;
	menu->settings = 0;
	menu->quit = 0;
	menu->menu_state = 1;
	menu->resolution = 0;
	menu->sensivity = 0;
	menu->settings_state = 0;
	menu->back = 0;
	menu->one = 0;
	menu->two = 0;
	menu->three = 0;
	menu->highlight = rgb_conv(255, 255, 255);
	menu->minimap = 0;
	menu->game_state = 0;
	menu->resolution_state = 0;
	menu->controls_state = 0;
	menu->extras_state = 0;
	menu->low_res = 0;
	menu->mid_res = 0;
	menu->high_res = 0;
}

void	load_menu(t_data *data)
{
	t_menu	*m;

	alloc_menu(data);
	m = data->menu;
	load_images(data, data->menu->background[BG], "assets/menu/background.xpm");
	load_images(data, m->background[NEW_GAME], "assets/menu2/new_game.xpm");
	load_images(data, m->background[EXIT], "assets/menu2/exit.xpm");
	load_images(data, m->background[LAYOUT], "assets/layout.xpm");
	load_images(data, m->background[LOGO], "assets/logo.xpm");
	load_images(data, m->background[CONTROLS], "assets/menu2/controls.xpm");
	load_images(data, m->background[BACK], "assets/menu2/back.xpm");
	load_images(data, m->background[NEW_BG], "assets/menu/background.xpm");
	load_images(data, m->background[EXTRAS], "assets/menu2/extras.xpm");
	load_images(data, m->background[CONTROLS_KEYS], \
	"assets/menu/control_keys.xpm");
	load_images(data, m->background[10], "assets/extra.xpm");
	init_menu_var(data);
}
