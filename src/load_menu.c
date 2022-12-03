#include "cub3d.h"

char *remove_char(char *str, char c)
{
	int	i;
	int j;
	char *tmp;
	i = 0;
	j = 0;

	while(str[i])
	{
		if (str[i + j] != c)
			i++;
		else
			j++;
	}
	tmp = malloc(sizeof(char) * i + 1);
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
	free(str);
	return (tmp);
}

int	load_images(t_data *data, t_img_data *image, char *path)
{
	int fd;
	char *buffer;
	char **tmp;

	buffer = NULL;
	fd = open(path,O_RDWR);
	buffer = get_next_line(fd);
	while (ft_strncmp(buffer, "\"",1))
	{
		buffer = get_next_line(fd);
	}
	buffer = remove_char(buffer, '\"');
	buffer = remove_char(buffer, ',');
	tmp = ft_split(buffer, ' ');
	close(fd);
	image->width = atoi(tmp[0]);
	image->height = atoi(tmp[1]);
	//free tmp
   	image->img = mlx_xpm_file_to_image(data->window->mlx, path, &image->width, &image->height);
   image->address = (int *)mlx_get_data_addr(image->img, &image->bpp, &image->line_len, &image->endian);
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

	load_images(data, data->menu->background[0], "assets/menu/background.xpm");
	load_images(data,data->menu->background[1], "assets/Menu_Pack_1/MenuButton.xpm");
	load_images(data,data->menu->background[2], "assets/Menu_Pack_1/PlayButton.xpm");
	load_images(data,data->menu->background[3], "assets/Menu_Pack_1/ExitButton.xpm");
	load_images(data,data->menu->background[4], "assets/layout.xpm");
	load_images(data,data->menu->background[5], "assets/logo.xpm");
	menu = data->menu;
	menu->off = 1;
	menu->on = 0;
	menu->options = 0;
	menu->start = 1;
	menu->quit = 0;
	menu->highlight = rgb_conv(255,255,255);
	menu->menu = 0;
}