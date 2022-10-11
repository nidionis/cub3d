#include "cub3d.h"

char	**ft_append_tab(char **matrix, char *str)
{
	int		tab_len;
	char	**new_tab;

	if (!str)
		return (matrix);
	tab_len = 0;
	if (matrix)
		while (matrix[tab_len])
			tab_len++;
	new_tab = malloc((tab_len++ + 2) * sizeof(char *));
	if (!new_tab)
		return (NULL);
	new_tab[tab_len--] = NULL;
	new_tab[tab_len] = str;
	while (tab_len--)
		new_tab[tab_len] = matrix[tab_len];
	free(matrix);
	matrix = NULL;
	return (new_tab);
}

int	ft_matrixlen(char **matrix)
{
	int	len;

	len = 0;
	if (matrix)
	{
		while (matrix[len])
			len++;
	}
	return (len);
}

void	print_tab(char **tab)
{
	while (*tab)
		printf("%s", *tab++);
}

char	**default_map(char	*argv[])
{
	char	**map;
	char	*line;
	int		fd;

	map = NULL;
	fd = open(argv[1], O_RDONLY);
	while ((line = get_next_line(fd)))
		map = ft_append_tab(map, line);
	return (map);
}

int	main(int argc, char *argv[])
{
	t_imgg	img;
	char	**map;
	(void)img;
	(void)argv;

	if (argc != 2)
		error_msg("Needs a path to the map file only");
	else
	{
		map = default_map(argv);
		print_tab(map);
		/*
		img.mlx_ptr = mlx_init();
		img_default_init(&img);
		if ((argv[1][0] == 'j' || argv[1][0] == 'J') && !argv[1][1])
			img.f = julia;
		else
			img.f = mandelbrot;
	}
	img.win_ptr = mlx_new_window(img.mlx_ptr, \
		img.size[0], img.size[1], "fractol");
	set_win_center(&img);
	img.img_ptr = mlx_new_image(img.mlx_ptr, \
		img.size[0], img.size[1]);
	img.addr = mlx_get_data_addr(img.img_ptr, \
		&(img.bpp), &(img.line_len), &(img.endian));
	img.f(&img);
	mlx_put_image_to_window(img.mlx_ptr, img.win_ptr, img.img_ptr, 0, 0);
	mlx_hook(img.win_ptr, ON_DESTROY, 0, quit, &img);
	mlx_key_hook(img.win_ptr, manage_keystroke, &img);
	mlx_mouse_hook(img.win_ptr, manage_mouse, &img);
	mlx_mouse_hook(img.win_ptr, manage_expose, &img);
	mlx_loop(img.mlx_ptr);
	*/
		ft_free_split(&map);
	}
}
