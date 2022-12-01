#include "cub3d.h"

int	load_images(t_data *data, t_img_data *image, char *path)
{
   	image->img = mlx_xpm_file_to_image(data->window->mlx, path, &image->width, &image->height);
   image->address = (int *)mlx_get_data_addr(image->img, &image->bpp, &image->line_len, &image->endian);
    return (0);
}

void	draw_image(t_data *data,int y, int x)
{
	int img_x;
	int img_y;

	img_x = 0;
	img_y = 0;
	while (img_y < 279)
	{
		while (img_x < 727)
		{
			data->menu->background[0]->address[y * 279 + x] = data->menu->background[1]->address[img_y * 279 + img_x];
			img_x++;
			x++;
		}
		y++;
		img_y++;
		x = 0;
		img_x = 0;
	}
}

void load_menu(t_data *data)
{
    t_menu *menu;

    data->menu = malloc(sizeof(t_menu));
	data->menu->background[0] = malloc(sizeof(t_img_data));
	data->menu->background[1] = malloc(sizeof(t_img_data));

    load_images(data, data->menu->background[0], "assets/menu/background.xpm");
	load_images(data,data->menu->background[1], "assets/MenuButton.xpm");
	draw_image(data,1000,1000);
    menu = data->menu;
    menu->off = 1;
    menu->on = 0;
    menu->options = 0;
    menu->start = 1;
    menu->quit = 0;
}