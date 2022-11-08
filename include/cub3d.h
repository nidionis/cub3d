/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suplayerko <suplayerko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 18:19:05 by suplayerko          #+#    #+#             */
/*   Updated: 2022/11/07 19:18:21 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifdef __APPLE__
#  define KEY_Q 12
#  define KEY_A 0
#  define KEY_Z 6
#  define KEY_W 13
#  define KEY_S 1
#  define KEY_X 7
#  define KEY_E 14
#  define KEY_D 2
#  define KEY_C 8
#  define KEY_R 15
#  define KEY_F 3
#  define KEY_RIGHT 124 
#  define KEY_LEFT 123 
#  define KEY_UP 126
#  define KEY_DOWN 125
#  define KEY_ESC 53
#  define KEY_IN 69
#  define KEY_OUT 78
#  include "../minilibx_mac/mlx.h"

# else   // LINUX
#  include <X11/keysym.h>   // 
#  include "../minilibx_linux/mlx.h"
#  include "../minilibx_linux/mlx_int.h"
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
/* EMPTY must be ' ', for the function format_map lets call lane the '0' */
# define LANE 32
# define EMPTY ' '
# define NORTH_CHAR 78
# define SOUTH_CHAR 83
# define WEST_CHAR 87
# define EAST_CHAR 69
/* for is_available_mapcase : keep directions at the end (see is_available_mapcase function) */
# define MAPCASES "01 "
/* MAPCASE to consider as a wall */
# define IS_BLOCK "1 "
# define SCREEN_WIDTH 1280
# define SCREEN_HEIGHT 720
# define RAYCAST_QUALITY 50
# define NB_TEXTURES 4
# define UNITS_PER_BOX 1000
# define STEPS_PER_BOX 8
# define WALL_SIZE 100
/* in radient 66 = 1.15*/
# define CAM_ANGLE 1.15
/* num of ray_parse for a pic */
# define CAM_QUALITY 1000
/* file deleted with make clean */
# define DEBUG_LOG_FILENAME "debug_file"
# define PI 3.141592654
# define DEFAULT_ROTATION_ANGLE (3.141592654 / 12.000)
# define PLAYER_MAP_ARROW 20
# define ORIGIN_PLANE_SCALE 1.0

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

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_player
{
	t_point		pos_map;
	t_point		pos_box;
	/* absolute positions */
	t_point		pos_in_step;
	t_point		pos_in_pix;
	t_vector	direction;
	int			angle;
}	t_player;

typedef struct s_image
{
	unsigned int	ceiling_color;
	unsigned int	floor_color;
	char			*texture_path[NB_TEXTURES];
	int				line_len;
}	t_image;

typedef struct	s_ray
{
	double		len;
	double		dist_from_plan;
	int			side;
	t_vector	direction;
	t_point		hit_point;
	double		direction_len;

	t_vector	side_distances;
	t_vector	delta_distances;
	t_vector	vector_sideX;
	t_vector	vector_sideY;
	t_vector	vector_deltaX;
	t_vector	vector_deltaY;
}	t_ray;

/* note: origin plane is a POINT using t_vector structure*/
typedef struct	s_cam
{
	t_vector	origin_plane;
	t_vector	plane_dir;
	double		plane_size;
	t_ray		*beam;
	t_ray		arRay[CAM_QUALITY];
}	t_cam;

//struct for window
typedef struct s_window
{
	void	*mlx;
	void	*init;
	int		width;
	int		height;
}	t_window;

// typedef struct s_raycasting
// {

// }	t_ray_casting;

typedef struct s_data
{
	char		*line;
	char		**line_split;
	char		*blocks;
	char		*map_cases;
	t_image		*image;
	t_player	*player;
	t_cam		*cam;
	t_window	*window;
	char		**map;
}	t_data;

enum x_or_y { _x, _y };
enum log_type { DATA, PARAM, CAM, PLAYER, MAP };
enum e_identifiers { NO, SO, WE, EA, F, C };
enum e_direction { N=1, S=2, W=10, E=20, NW=11, SW=12, SE=22, NE=21 };
enum e_cardinal { NORTH, SOUTH, EAST, WEST };
enum e_player_direction{ FORWARD, BACKWARD, RIGHT, LEFT, NB_DIRECTION };

void			error_msg(char *msg);
char	**default_map(char	*argv[]);
char	**ft_append_tab(char **matrix, char *str);
char	*get_next_line(int fd);
int func(void);
int	conv_id_param(t_data *data, int identifier_len, char *str);
void	file_extention_available(t_data *data, char *fname);
int	ft_matrixlen(char **matrix);
int	get_identifier(t_data *data, char *str);
int	import_params(t_data *data);
void	parse_file(char *fname, t_data	*s);
int	parsing_loop(t_data *data, int *map_parse);
t_player	*default_player(void);
t_point	get_vector(t_point *from, t_point *to);
t_vector	vec_diff(t_vector v1, t_point v2);
t_vector	vec_scale(t_vector vec, double scale);
void init_null(t_data *data, int *map_parse);
void	add_vec(t_point	*pt, t_point vec);
void	clean_exit(t_data *data, int exit_code);
void	exit_msg(t_data *data, char *msg, int ret_exit);
void	import_param(t_data *data, int identifier, char *line);
void	ray_parse(t_data *data);
void	wrong_color(t_data *data, char *color_strimed);
int	is_blank_line(char *line);
int	is_blank_char(char c);
int	is_map_line(t_data *data, char *str);
int	check_map(t_data *data);
unsigned int	init_f_c_color(t_data *s, char *line);
void	print_player(t_data *data, int fd);
void	print_params(t_data *data, int fd);
void	print_map(t_data *data, int fd);
void	print_s(t_data *data, int fd);
void	redir_debug_file_logs(t_data *data, char *fname, int log_type);
void	init_player(t_data *data, int x, int y, int *is_player);
void	init_fd(t_data *data, int *fd, char *fname);


int	check_wall(t_data *data, int crossover_direction);
int	check_update_box_pos(t_data *data);
int	move_player(t_data *data, int direction);
void	translate_pt(t_vector vector, t_point *pt);
double	distance_point_to_vector(t_point point, t_point v_p1, t_point v_p2);
t_point	make_point(int x, int y);
int	north_crossing(t_data *data);
int	south_crossing(t_data *data);
int	east_crossing(t_data *data);
int	west_crossing(t_data *data);
void	rotate_vector(t_vector *vector, double radian_angle);
double	degree_to_radian(double degree_angle);
int	corner_crossing(t_data *data);
int	is_block(t_data *data, char c);
void	redir_debug_file_msg(char *fname, char *msg);
void	rotate_player(t_player *player, int move);
int	is_available_mapcase(t_data *data, int x, int y, int *is_player);
int	is_block(t_data *data, char c);
int	is_mapcase(t_data *data, char c);
int	is_NSEW(char c);
void	init_cam_vector(t_data *data);
t_point	get_player_absolute_position(t_player *player);
void	clean_useless_empty_splace(char	**map);
void	rectangle_map(t_data *data, char **map);
void	format_map(t_data *data);
unsigned int	rgb_conv(int R, int G, int B);
void	translate_vector_as_pt(t_vector vector, t_vector *pt);
t_point	update_pos_in_pix(t_player *player);
t_point	update_pos_in_step(t_player *player);
void	init_cam_vector(t_data *data);
void	set_camera(t_data *data);
double	vec_len(t_vector vector);
t_vector	convert_pt_to_vec(t_point p);
void	set_delta_distance(t_data *data);
void	set_side_distance(t_data *data);
char	pix_pos_to_map_case(t_point absolute_pos, char **map);
double	vectors_angle_cos(t_vector v1, t_vector v2);
void	draw_wall_line(t_data *data, int i);
int	ray_cast(t_data *data);
void	set_arRay(t_data *data);

//duarte functions
int	window_init(t_window *window);
int	render_map_2d(t_data *data);
int	player_init(char **map, t_player *player);
int	key_event(int key, t_data *data);
int exit_game(t_data *data);
void	draw_line(t_data *data, t_point	*start, t_point	*end, int color);
#endif
