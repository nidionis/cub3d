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

typedef struct s_player
{
	/* in square */
	t_point		pos_map;
	double		speed;
	double		rotate_speed;
	/* in pix or UNITS_PER_BOX*/
	t_point		pos_box;
	/* absolute positions */
	t_point		pos_in_step;
	t_point		pos_in_pix;
	t_vector	map_pos;
	t_vector	direction;
	
	int			angle;
}	t_player;

typedef struct	s_sprite
{
	//texture
	t_point	pos;

	struct s_sprite	*next;
}	t_sprite;

typedef struct s_image
{
	unsigned int	ceiling_color;
	unsigned int	floor_color;
	char			*texture_path[NB_TEXTURES];
	//char			*minimap_texture[NB_MINIMAP_TEXTURES]
	int				line_len;
	t_sprite		*sprite_ls;
	int				sprite_half_size;
}	t_image;

typedef struct	s_obstacle
{
	char				type;
	double				len;
	// if type is IS_BLOCK
	t_point				hit_point;
	int					side;
	// if type is SPRITE
	double				sprite_hit; //distance from sprite_point to ray
	t_sprite			*sprite_pointer;
	struct s_obstacle	*next;
}	t_obstacle;

typedef struct	s_rayponse
{
	double		len;
	double		dist_from_plan;
	int			side;
	t_point		hit_point;
	t_obstacle	*obstacles_ls;
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
	char *adress;
	int	bpp;
	int line_len;
	int endian;
}	t_img_data;

typedef struct s_texture
{
	t_img_data	*img;
	int		size[2];
}	t_texture;

typedef struct s_key_status
{
	unsigned int	w;
	unsigned int	s;
	unsigned int	a;
	unsigned int	d;
	unsigned int	left;
	unsigned int	right;
}	t_key_status;

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
	int				map_size_in_units[2];
	t_texture		wall_textures[NB_TEXTURES];
	t_img_data		*img;
	t_key_status	*key_status;
}	t_data;

enum x_or_y { _x, _y };
enum log_type { DATA, PARAM, CAM, PLAYER, MAP };
enum e_identifiers { NO, SO, EA, WE, F, C };
enum e_direction { N=1, S=2, W=10, E=20, NW=11, SW=12, SE=22, NE=21 };
enum e_cardinal { NORTH, SOUTH, EAST, WEST };
enum e_player_direction{ FORWARD, BACKWARD, RIGHT, LEFT, NB_DIRECTION };
enum e_sprite {SPRITE = -1};
enum e_others {LINE_WIDTH = SCREEN_WIDTH / CAM_QUALITY, LINE_HEIGTH_SCALE = SCREEN_HEIGHT * UNITS_PER_BOX};
