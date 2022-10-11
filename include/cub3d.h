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
# define NORTH 'N'
# define SOUTH 'S'
# define WEST 'W'
# define EAST 'E'

//COLORS 
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"

# include <stdlib.h>
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

/*
	bbp = bit_per_pixels
	scale (0: x, 1: y) = pixels per units
*/
typedef struct s_imgg
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
	unsigned int	size[2];
	unsigned int	scale[2];
	t_pix			center;
	t_pix			win_center;
	void			(*f)();
	float			quality;
	unsigned int	color_shift;
	t_pt			julia_coef;
}	t_imgg;

void			error_msg(char *msg);

/* img */
unsigned int	get_offset(t_pix pix, t_img *data);
void			put_pix(t_img *data, t_pix pix, int color);
unsigned int	rgb_conv(int R, int G, int B);
unsigned int	color_render(unsigned int color_byte, t_img *img);
t_pix			convert_pt_to_pix(t_img *img, t_pt pt, t_pix center);
t_pt			convert_pix_to_pt(t_img *img, t_pix pix, t_pix center);
void			orthonorm(t_img *img);
void			orthonorm_rel(t_img *img);
void			circle(t_img *img, int r, t_pix center, unsigned int color);
void			rectangle(t_img *img, int L, int H, t_pix origin);
void			set_win_center(t_img *img);
void			img_default_init(t_img	*img);

/* vectors */
t_pix			get_vector(t_pix *from, t_pix *to);
t_pix			vec_scale(t_pix vec, double scale);
void			apply_vec(t_pix	*pt, t_pix vec);
t_pix			vec_diff(t_pix v1, t_pix v2);
t_pix			make_pix_pt(int x, int y);

/* hooks */
t_img			*zoom_in(t_img *img, void (*f)(), int x, int y);
t_img			*zoom_out(t_img *img, void (*f)(), int x, int y);
int				manage_keystroke(int keystroke, void *params);
int				manage_mouse(int button, int x, int y, void *param);
void			moving(t_img *img, void (*f)(), int keystroke);
void			recentrer(t_img *img, int x, int y);

/* fractales */
t_pt			complex_square(t_pt complex_nb);
void			mandelbrot(t_img *img);
void			julia(t_img *img);
void			carpette(t_img *img);

#endif
