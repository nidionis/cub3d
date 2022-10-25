/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:19:05 by supersko          #+#    #+#             */
/*   Updated: 2022/10/25 13:47:48 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifdef __APPLE__
#  define TOUCH_A 0
#  define TOUCH_W 13
#  define TOUCH_S 1
#  define TOUCH_D 2
#  define TOUCH_RIGHT 124
#  define TOUCH_LEFT 123
#  define TOUCH_UP 126
#  define TOUCH_DOWN 125
#  define TOUCH_ESC 53

# else   // LINUX
#  include <X11/keysym.h>   // 
#  define KEY_Q 113
#  define KEY_A 97
#  define KEY_Z 122
#  define KEY_W 119
#  define KEY_S 115
#  define KEY_X 120
#  define KEY_E 101
#  define KEY_D 100
#  define KEY_C 99
#  define KEY_R 114
#  define KEY_F 102
#  define KEY_RIGHT 65363 
#  define KEY_LEFT 65361 
#  define KEY_UP 65362
#  define KEY_DOWN 65364
#  define KEY_ESC 65307
#  define KEY_IN 61
#  define KEY_OUT 45
#  define EXPOSE_X 65293
#  define ON_DESTROY 	17
#  include "../mlx_linux/mlx.h"
#  include "../mlx_linux/mlx_int.h"
# endif

# define CLIC 1
# define ON_MOUSEDOWN  4
# define ON_MOUSEUP 5
# define LEFT_ARROW 123
# define RIGH_ARROW 124
# define DOWN_ARROW 125
# define UP_ARROW 126

//MACROS 
# define WALL 49
# define FLOOR 48
# define EMPTY 32
# define NORTH 78
# define SOUTH 83
# define WEST 87
# define EAST 69
/* for is_available_mapcase : keep directions at the end */
# define MAPCASES "01 NSEW"
# define SCREEN_WIDTH 640
# define SCREEN_HEIGHT 480
# define RAYCAST_QUALITY 50

//COLORS 
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"


# include <stdlib.h>
# include "../libft/libft.h"
# include <unistd.h>
# include <math.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h> // test
# include <time.h>
# include <stdint.h>

typedef struct s_pix
{
	int	x;
	int	y;
}	t_pix;

typedef struct s_pt
{
	double	x;
	double	y;
}	t_pt;

typedef struct s_person
{
	t_pt	pos;
	t_pt	dir;
	t_pt	plane;
}	t_person;

typedef struct s_imgg
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	char			*addr;
	int				bpp;
	unsigned int	size[2];
	unsigned int	ceiling_color;
	unsigned int	floor_color;
	char			*texture_path[4];
	//unsigned int	scale[2];
	//t_pix			center;
	//t_pix			win_center;
	void			(*f)();
}	t_imgg;

typedef struct s_s
{
	char		*line;
	char		**line_split;
	t_imgg		*i;
	t_person	*p;
	char		**map;
}	t_s;

enum _identifiers { NO, SO, WE, EA, F, C };

void			error_msg(char *msg);

char	**default_map(char	*argv[]);
char	**ft_append_tab(char **matrix, char *str);
char	*get_next_line(int fd);
int func(void);
int	conv_id_param(t_s *s, int identifier_len, char *str);
int	file_extention_available(char *fname);
int	ft_matrixlen(char **matrix);
int	get_identifier(t_s *s, char *str);
int	import_params(t_s *s);
int	parse_file(char *fname, t_s	*s);
int	parsing_loop(t_s *s, int *map_parse);
t_person	*default_person(void);
t_pix	get_vector(t_pix *from, t_pix *to);
t_pix	vec_diff(t_pix v1, t_pix v2);
t_pix	vec_scale(t_pix vec, double scale);
void init_null(t_s *s, int *fd, char *fname, int *map_parse);
void	add_vec(t_pix	*pt, t_pix vec);
void	clean_exit(t_s *s, int exit_code);
void	exit_msg(t_s *s, char *msg, int ret_exit);
void	import_param(t_s *s, int identifier, char *line);
void	print_tab(char **tab);
void	ray_parse(t_s *s);
void	wrong_color(t_s *s, char *color_strimed);
int	is_blank_line(char *line);
int	is_blank_char(char c);
int	is_map_line(char *str);
int	check_map(t_s *s);
unsigned int	init_f_c_color(t_s *s, char *line);
#endif
