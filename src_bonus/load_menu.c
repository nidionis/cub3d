/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 03:41:47 by dpaulino          #+#    #+#             */
/*   Updated: 2023/01/02 12:56:14 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub3d_bonus.h"

char	*remove_char(char *str, char c)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;

	tmp = malloc(sizeof(char) * 30);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			tmp[j] = str[i];
			j++;
		}
		i++;
	}
	tmp[j] = '\0';
	return (tmp);
}

t_point	get_img_size(t_data *data, char *path)
{
	int		fd;
	char	*buffer;
	char	*buffer2;
	char	**tmp;
	t_point	size;
	(void)data;
	buffer2 = NULL;
	buffer = NULL;
	fd = open(path, O_RDWR);
	if (fd == -1)
	{
		printf("%s <-- File does not exit\n", path);
		exit(0);
	}
	buffer = get_next_line(fd);
	while (ft_strncmp(buffer, "\"", 1))
	{
		free(buffer);
		buffer = get_next_line(fd);
	}
	buffer2 = remove_char(buffer, '\"');
	free(buffer);
	buffer = remove_char(buffer2, ',');
	free(buffer2);
	tmp = ft_split(buffer, ' ');
	close(fd);
	size.x = atoi(tmp[0]);
	size.y = atoi(tmp[1]);
	ft_free_split(&tmp);
	free(buffer);
	return (size);
}

int	load_images(t_data *data, t_img_data *image, char *path)
{
	t_point	size;

	size = get_img_size(data, path);
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

void	draw_image(t_img_data *img1, t_img_data *img2, t_point pos, int color)
{
	int	img_x;
	int	img_y;
	int	tmp_x;

	tmp_x = pos.x;
	img_x = 0;
	img_y = 0;
	while (img_y < img2->height)
	{
		while (img_x < img2->width)
		{
			if (img2->address[img_y * img2->width + img_x] == -16777216)
			{
				img_x++;
				pos.x++;
			}
			else
			{
				if (color != -1)
				{
					if (img2->address[img_y * img2->width + img_x] != 0)
						img1->address[pos.y * img1->line_len / 4 + pos.x] = color;
				}
				else
					img1->address[pos.y * img1->line_len / 4 + pos.x] = img2->address[img_y * img2->width + img_x];
				img_x++;
				pos.x++;
			}
		}
		pos.y++;
		img_y++;
		pos.x = tmp_x;
		img_x = 0;
	}
}

void load_menu(t_data *data)
{
	t_menu *menu;

	data->menu = malloc(sizeof(t_menu));
	data->menu->background[0] = malloc(sizeof(t_img_data));
	data->menu->background[1] = malloc(sizeof(t_img_data));
	data->menu->background[2] = malloc(sizeof(t_img_data));
	data->menu->background[3] = malloc(sizeof(t_img_data));
	data->menu->background[4] = malloc(sizeof(t_img_data));
	data->menu->background[5] = malloc(sizeof(t_img_data));
	data->menu->background[6] = malloc(sizeof(t_img_data));
	data->menu->background[7] = malloc(sizeof(t_img_data));
	data->menu->background[8] = malloc(sizeof(t_img_data));
	data->menu->background[9] = malloc(sizeof(t_img_data));
	data->menu->background[10] = malloc(sizeof(t_img_data));
	data->menu->background[11] = malloc(sizeof(t_img_data));
	data->menu->background[12] = malloc(sizeof(t_img_data));
	data->menu->background[CONTROLS_KEYS] = malloc(sizeof(t_img_data));
	data->menu->background[LOW_RES] = malloc(sizeof(t_img_data));
	data->menu->background[MID_RES] = malloc(sizeof(t_img_data));
	data->menu->background[HIGH_RES] = malloc(sizeof(t_img_data));
	data->menu->background[17] = malloc(sizeof(t_img_data));
	load_images(data, data->menu->background[BG], "assets/menu/background.xpm");
	load_images(data,data->menu->background[SETTINGS], "assets/menu2/settings.xpm");
	load_images(data,data->menu->background[NEW_GAME], "assets/menu2/new_game.xpm");
	load_images(data,data->menu->background[EXIT], "assets/menu2/exit.xpm");
	load_images(data,data->menu->background[LAYOUT], "assets/layout.xpm");
	load_images(data,data->menu->background[LOGO], "assets/logo.xpm");
	load_images(data,data->menu->background[6], "assets/menu2/settings.xpm");
	load_images(data,data->menu->background[RESOLUTION], "assets/menu2/resolution.xpm");
	load_images(data,data->menu->background[SENSIVITY], "assets/menu2/sensivity.xpm");
	load_images(data,data->menu->background[CONTROLS], "assets/menu2/controls.xpm");
	load_images(data,data->menu->background[BACK], "assets/menu2/back.xpm");
	load_images(data, data->menu->background[NEW_BG], "assets/menu/background.xpm");
	load_images(data, data->menu->background[EXTRAS], "assets/menu2/extras.xpm");
	load_images(data, data->menu->background[CONTROLS_KEYS], "assets/menu/control_keys.xpm");
	load_images(data, data->menu->background[LOW_RES], "assets/menu2/700x500.xpm");
	load_images(data, data->menu->background[MID_RES], "assets/menu2/1200x700.xpm");
	load_images(data, data->menu->background[HIGH_RES], "assets/menu2/1900x1080.xpm");
	load_images(data, data->menu->background[17], "assets/extra.xpm");
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
