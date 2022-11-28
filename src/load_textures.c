#include "../include/cub3d.h"

void	load_textures(t_data *data)
{
	t_window *window;

	int width;
	int height;

	width = 20;
	height = 20;
	window = data->window;
	data->textures = malloc(sizeof(t_img_data));
	data->textures->img = mlx_xpm_file_to_image(window->mlx, \
	"assets/wall.xpm", &width, &height);
	data->textures->adress = mlx_get_data_addr(data->textures->img, \
	&data->textures->bpp, &data->textures->line_len, &data->textures->endian);
}