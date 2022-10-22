/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:19:05 by supersko          #+#    #+#             */
/*   Updated: 2022/10/10 13:11:05 by supersko         ###   ########.fr       */
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
# define WALL '1' 
# define FLOOR '0'
# define EMPTY ' '
# define NORTH 'N'
# define SOUTH 'S'
# define WEST 'W'
# define EAST 'E'
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
# include <X11/keysym.h>   // 
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
	t_imgg		*i;
	t_person	*p;
	char		**map;
}	t_s;

enum _identifiers { NO, SO, WE, EA, F, C };

void			error_msg(char *msg);

/* img */
unsigned int	get_offset(t_pix pix, t_imgg *data);
void			put_pix(t_imgg *data, t_pix pix, int color);
unsigned int	rgb_conv(int R, int G, int B);
unsigned int	color_render(unsigned int color_byte, t_imgg *img);

/* vectors */
t_pix			get_vector(t_pix *from, t_pix *to);
t_pix			vec_scale(t_pix vec, double scale);
void			add_vec(t_pix	*pt, t_pix vec);
t_pix			vec_diff(t_pix v1, t_pix v2);
t_pix			make_pix_pt(int x, int y);

/* hooks */
int				manage_keystroke(int keystroke, void *params);
int				manage_mouse(int button, int x, int y, void *param);

/* str */
char			*get_next_line(int fd);

/* matrix */
char			**default_map(char	*argv[]);
void			print_tab(char **tab);
int				ft_matrixlen(char **matrix);
char			**ft_append_tab(char **matrix, char *str);
int	parse_file(char *fname, t_s	*s);
#endif
