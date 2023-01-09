/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 17:54:37 by dpaulino          #+#    #+#             */
/*   Updated: 2023/01/09 14:38:37 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
#  define ENTER 36
#  define KEY_M 46
#  define SHIFT 257
#  define KEY_P 35
#  include <mlx.h>

# else   // LINUX
#  include <X11/keysym.h>   // 
#  include "../libmlx/mlx.h"
// #  include "../minilibx_linux/mlx_int.h"
#  define ENTER 65293
#  define KEY_P 112
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
#  define KEY_M 109
#  define SHIFT 65505
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
# define DOOR '2'
# define RED_SWITCH '3'
# define GREEN_SWITCH '4'
# define MINIMAP '5'
# define KEY '6'
/* for is_available_mapcase : keep directions at the end (see is_available_mapcase function) */
# define MAPCASES "01 "
/* MAPCASE to consider as a wall */
# define IS_BLOCK "12345 "
# define NB_TEXTURES 4
# define SCREEN_WIDTH 1900
# define SCREEN_HEIGHT 1080
/* should be eaual to windows width*/
# define CAM_QUALITY 1900
# define NB_TEXTURES 4
# define NB_MENU_IMG 12
# define BONUS_TEXTURES_SOLIDS "assets/door_bin.xpm,assets/door_bin.xpm,assets/door_bin.xpm,assets/door_bin.xpm,\
assets/button_off.xpm,assets/button_off.xpm,assets/button_off.xpm,assets/button_off.xpm,\
assets/button_on.xpm,assets/button_on.xpm,assets/button_on.xpm,assets/button_on.xpm,\
assets/mapper.xpm,assets/mapper.xpm,assets/mapper.xpm,assets/mapper.xpm"
# define SPRITES_TEXTURES ""
# define UNITS_PER_BOX 100
# define STEPS_PER_BOX 30
# define WALL_SIZE 11
# define WALL_SIZE2 19
/* in radient 66 = 1.15*/
/* num of ray_parse for a pic */
# define CAM_ANGLE 1.15
# define ORIGIN_PLANE_SCALE 1.0
/* file deleted with make clean */
# define DEBUG_LOG_FILENAME "debug_file"
# define PI 3.141592654
# define DEFAULT_ROTATION_ANGLE (3.141592654 / 48.000)
# define PLAYER_MAP_ARROW 20

//COLORS 
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
//macro for img indexes
# define BG 0
# define NEW_GAME 1
# define EXIT 2
# define LAYOUT 3
# define LOGO 4
# define CONTROLS 5
# define BACK 6
# define NEW_BG 7
# define EXTRAS 8
# define CONTROLS_KEYS 9
