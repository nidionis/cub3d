#include "cub3d.h"

typedef struct  s_list {
    void            *content;
    struct s_list   *next;
}   t_list;

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

typedef struct	s_obstacle t_obstacle;

typedef struct s_player
{
	/* in square */
	t_point		pos_map;
	int		speed;
	double		rotate_speed;
	/* in pix or UNITS_PER_BOX*/
	t_point		pos_box;
	/* absolute positions */
	t_point		pos_in_step;
	t_point		pos_in_pix;
	t_vector	map_pos;
	t_vector	direction;
	unsigned 	int stamina;
	int			angle;
}	t_player;

typedef struct	s_sprite
{
	int type;
	t_point	pos;
}	t_sprite;

typedef struct s_image
{
	unsigned int	ceiling_color;
	unsigned int	floor_color;
	char			*texture_path[NB_TEXTURES];
	int				line_len;
	t_sprite		*sprite_ls;
	int				sprite_half_size;
}	t_image;

typedef struct	s_rayponse
{
	double		len;
	double		dist_from_plan;
	int			side;
	t_point		hit_point;
	t_list	*obstacles_ls;
}	t_rayponse;

typedef struct	s_ray
{
	t_vector	direction;
	double		direction_len;
	double		side_distances[2];
	double		delta_distances[2];
}	t_ray;

/* note: origin plane is a POINT using t_vector structure*/
typedef struct	s_cam
{
	t_vector	origin_plane;
	t_vector	plane_dir;
	double		plane_size;
	t_ray		*beam;
	t_rayponse	arRay[CAM_QUALITY];
}	t_cam;

//struct for window
typedef struct s_window
{
	void	*mlx;
	void	*init;
	int		width;
	int		height;
}	t_window;

typedef struct s_img_data
{
	void *img;
	int *address;
	char *adress;
	int	bpp;
	int line_len;
	int line_height;
	int endian;
	int width;
	int height;
}	t_img_data;

typedef struct	s_obstacle
{
	char				type;
	double				dist;
	int				textureX;
	t_img_data			*texture;
}	t_obstacle;

typedef struct s_key_status
{
	unsigned int	w;
	unsigned int	s;
	unsigned int	a;
	unsigned int	d;
	unsigned int	left;
	unsigned int	right;
	unsigned int	sprint;
	unsigned int	config;
}	t_key_status;

typedef struct s_menu
{
	//menu
	unsigned int new_game;
	unsigned int controls;
	unsigned int extras;
	unsigned int settings;
	unsigned int quit;
	unsigned int menu_state;
	//settings
	unsigned int resolution;
	unsigned int sensivity;
	unsigned int settings_state;
	//other
	unsigned int game_state;
	unsigned int highlight;
	unsigned int back;
	unsigned int one;
	unsigned int two;
	unsigned int three;
	unsigned int minimap;
	//resolution
	unsigned int low_res;
	unsigned int mid_res;
	unsigned int high_res;
	unsigned int resolution_state;
	unsigned int controls_state;
	unsigned int extras_state;
	t_img_data		*background[20];
} t_menu;

typedef struct s_data
{
	char			*line;
	char			**line_split;
	char			*blocks;
	char			*map_cases;
	t_image			*image;
	t_player		*player;
	t_cam			*cam;
	t_window		*window;
	char			**map;
	int			map_size_in_units[2];
	t_img_data		*wall_textures[NB_TEXTURES];
	t_img_data		*bonus_textures;
	t_img_data		*sprite_textures;
	t_img_data		*img;
	t_key_status	*key_status;
	t_menu			*menu;
	time_t			timer;
	int				time_state;
	int				mouse;
	int				map_width;
	int				map_height;
		int			rain_state;
}	t_data;

enum x_or_y { _x, _y };
enum log_type { DATA, PARAM, CAM, PLAYER, MAP };
enum e_identifiers { NO, SO, EA, WE, F, C };
enum e_direction { N=1, S=2, W=10, E=20, NW=11, SW=12, SE=22, NE=21 };
enum e_cardinal { NORTH, SOUTH, EAST, WEST };
enum e_player_direction{ FORWARD, BACKWARD, RIGHT, LEFT, NB_DIRECTION };
enum e_sprite {SPRITE = -1};
enum e_others {LINE_WIDTH = (int)SCREEN_WIDTH / (int)CAM_QUALITY, LINE_HEIGHT = (int)SCREEN_HEIGHT * (int)UNITS_PER_BOX};
//int LINE_WIDTH = (int)SCREEN_WIDTH / (int)CAM_QUALITY;
//int LINE_HEIGHT = (int)SCREEN_HEIGHT * (int)UNITS_PER_BOX;
