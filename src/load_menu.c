#include "cub3d.h"

int load_menu_images(t_data *data)
{
    t_img_data *background;

    background = data->menu->background;
   data->menu->background->img = mlx_xpm_file_to_image(data->window->mlx, "assets/menu/background.xpm", &background->width, &background->height);
    background->address = (int *)mlx_get_data_addr(background->img, &background->bpp, &background->line_len, &background->endian);
    return (0);
}

void init_menu(t_data *data)
{
    t_menu *menu;
    
    data->menu = malloc(sizeof(t_menu));
    menu = data->menu;
    menu->background = malloc(sizeof(t_img_data));
    menu->off = 1;
    menu->on = 0;
    menu->options = 0;
    menu->start = 0;
    menu->quit = 0;
    load_menu_images(data);
}