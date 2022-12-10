#include <cub3d.h>

void	import_bonus_textures(t_data *data)
{
	int	i;
	char	**fnames;
	int	nb_textures;
	t_img_data	*t;

	i = 0;
	fnames = ft_split(BONUS_TEXTURES_SOLIDS, ',');
	nb_textures = ft_matrixlen(fnames);
	data->bonus_textures = malloc(sizeof(t_img_data) * nb_textures + 1);
	while (i < nb_textures)
	{
		t = &data->bonus_textures[i];
		load_images(data, t, fnames[i]);
		if (!t->img)
			exit_msg(data, "[import_textures] Pb loading xpm file", 1);
		i++;
	}
	ft_free_split(&fnames);
}

/*
void	import_sprites_textures(t_data *data)
{
	int	i;
	char		**fnames;
	int		nb_textures;
	t_img_data	*t;

	i = 0;
	fnames = ft_split(SPRITES_TEXTURES, ',');
	nb_textures = ft_matrixlen(fnames);
	data->bonus_textures = malloc(sizeof(t_img_data) * nb_textures);
	while (i < nb_textures)
	{
		t = data->bonus_textures[i];
		t->img = mlx_xpm_file_to_image(data->window->mlx, fnames[i], &t->line_len, &t->line_height);
		t->adress = mlx_get_data_addr(t->img, &t->bpp, &t->line_len, &t->endian);
		if (!t->img)
			exit_msg(data, "[import_textures] Pb loading xpm file", 1);
		data->bonus_textures[i] = t;
		i++;
	}
	ft_free_split(&fnames);
}
*/
