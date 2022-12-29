SHELL	= /bin/bash
MAKEFLAGS += --silent

NAME    = cub3D
NAMEBONUS = cub3d_bonus
CC      = gcc
FLAGS	= -Wall -Wextra -Werror -g -Ofast -march=native -fsanitize=address
LFLAGS	= -Llibft -lft
###
SRCDIR	= src/
SRCFILE	=	bonus_raycasting.c  check_path_map.c     draw_interface.c   ft_list.c        keys_menu.c        map_ft.c             parse_check_map.c    player_init.c        rotate_player.c \
bonus_render2.c     check_path_switch.c  draw_line.c        game_event.c     keys_resolution.c  matrix.c             parse_file_colors.c  pos_update.c         soundtracks.c \
bonus_render.c      cub3d_render.c       draw_line_utils.c  generate_map.c   keys_settings.c    mouse.c              parse_format_map.c   raycasting.c         str_ft.c \
bonus_textures.c    draw_compass.c       end_game.c         get_next_line.c  load_menu.c        move_crossing_box.c  parse_import.c       raycasting_utils.c   utils2.c \
camera_ft.c         draw_functions2.c    exit_ft.c          key_event.c      load_window.c      move_player.c        parse_init.c         ray_set_distances.c  utils.c \
check_path_door.c   draw_functions.c     free_functions.c   keys_game.c      main.c             move_to_corner.c     parse_params.c       render_menu.c        vector_ft.c
SRCS	= $(addprefix $(SRCDIR), $(SRCFILE))
OBJDIR	= obj/
OBJFILE = $(SRCFILE:.c=.o)
OBJS	= $(addprefix $(OBJDIR), $(OBJFILE))
###
SRC_BONUSDIR	= src_bonus/
SRC_BONUSFILE	=	bonus_raycasting.c  check_path_map.c     draw_interface.c   ft_list.c        keys_menu.c        map_ft.c             parse_check_map.c    player_init.c        rotate_player.c \
bonus_render2.c     check_path_switch.c  draw_line.c        game_event.c     keys_resolution.c  matrix.c             parse_file_colors.c  pos_update.c         soundtracks.c \
bonus_render.c      cub3d_render.c       draw_line_utils.c  generate_map.c   keys_settings.c    mouse.c              parse_format_map.c   raycasting.c         str_ft.c \
bonus_textures.c    draw_compass.c       end_game.c         get_next_line.c  load_menu.c        move_crossing_box.c  parse_import.c       raycasting_utils.c   utils2.c \
camera_ft.c         draw_functions2.c    exit_ft.c          key_event.c      load_window.c      move_player.c        parse_init.c         ray_set_distances.c  utils.c \
check_path_door.c   draw_functions.c     free_functions.c   keys_game.c      main.c             move_to_corner.c     parse_params.c       render_menu.c        vector_ft.c

SRCS_BONUS	= $(addprefix $(SRC_BONUSDIR), $(SRC_BONUSFILE))
OBJ_BONUSDIR	= obj_bonus/
OBJ_BONUSFILE = $(SRC_BONUSFILE:.c=.o)
OBJS_BONUS	= $(addprefix $(OBJ_BONUSDIR), $(OBJ_BONUSFILE))
###
RM      = rm -rf
LIBHDR  = libft/libft.h
INCDIR  = include/
CUBHDR  = $(addprefix $(INCDIR), cub3d.h)
###
INC_BONUSDIR = include_bonus/
CUB_BONUSHDR  = $(addprefix $(INC_BONUSDIR), cub3d.h)
LBFOLDER  = .lb

UNAME	= $(shell uname -s)

ifeq ($(UNAME), Darwin)
	MLXFLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit
	MLX		= mlx
	ECHO = echo
endif

ifeq ($(UNAME), Linux)
	MLXFLAGS = -Lmlx_linux -lmlx -Imlx_linux -lXext -lX11 -lm -lz
	MLX		= minilibx_linux
	GOINFRE = .
	ECHO = echo -e
endif

N := x
C = $(words $N)$(eval N := x $N)

all: $(NAME) ;

bonus: $(NAMEBONUS) ;

$(NAME): set_main_count $(OBJS)
	@echo
	@echo -e "\033[1;33m"$(NAME) "objs are up to date."'\033[0m'
	@make -C libft
	@make -C $(MLX)
	@$(CC) $(FLAGS) $(OBJS) $(LFLAGS) $(MLXFLAGS) $(DEFINES) -o $(NAME)
	@echo -e "\033[1;43m"$(NAME) "is up to date."'\033[0m'

$(NAMEBONUS): set_bonus_count $(OBJS_BONUS)
	@mkdir -p $(LBFOLDER)
	@echo
	@echo -e "\033[1;33m"$(NAME)"_bonus" "objs are up to date."'\033[0m'
	@make -C libft
	@make -C $(MLX)
	@$(CC) $(FLAGS) $(OBJS_BONUS) $(SNDLIB) $(LFLAGS) $(MLXFLAGS) $(DEFINES) -o $(NAMEBONUS)
	@echo -e "\033[1;33m"$(NAME)"_bonus" "is up to date."'\033[0m'

$(OBJDIR)%.o: $(SRCDIR)%.c $(CUB_HDR)
	@mkdir -p $(OBJDIR)
	@$(CC) $(FLAGS) -c $< -o $@ -include $(LIBHDR) -include $(CUBHDR) $(DEFINES)
	@printf "\r"
	$(eval FILES_COMPILED := $(C))
	$(eval FILES_LEFT := $(shell expr $(FILES_COUNT) - $(FILES_COMPILED) + 1))
	printf '%0.s\033[0;46m \033[0m' {1..$(FILES_COMPILED)}
	printf '%0.s ' {1..$(FILES_LEFT)}
	printf "[ $(FILES_COMPILED)/$(FILES_COUNT) ]"

$(OBJ_BONUSDIR)%.o: $(SRC_BONUSDIR)%.c $(CUB_BONUSHDR) $(CUB_BONUSINC)
	@mkdir -p $(OBJ_BONUSDIR)
	@$(CC) $(FLAGS) -c $< -o $@ -include $(LIBHDR) -include $(CUB_BONUSHDR) $(DEFINES)
	@printf "\r"
	$(eval FILES_COMPILED := $(C))
	$(eval FILES_LEFT := $(shell expr $(FILES_COUNT) - $(FILES_COMPILED) + 1))
	printf '%0.s\033[0;46m \033[0m' {1..$(FILES_COMPILED)}
	printf '%0.s ' {1..$(FILES_LEFT)}
	printf "[ $(FILES_COMPILED)/$(FILES_COUNT) ] "

clean:
	@$(RM) $(OBJDIR)
	@echo -e '\033[1;31m'$(NAME) "ALL OBJECTS DELETED."'\033[0m'
	@$(RM) $(OBJ_BONUSDIR)
	@echo -e '\033[1;31m'$(NAME)"_bonus" "ALL OBJECTS FROM BONUS DELETED."'\033[0m'

clean_proj_files: clean
	@$(RM) $(NAME)
	@$(RM) $(NAMEBONUS)

fclean: clean_proj_files
	@make -C libft fclean
	@make -C $(MLX) clean
	@echo -e '\033[1;31m'$(NAME) "deleted."'\033[0m'

re: fclean all

set_bonus_count:
	$(eval FILES_COUNT := $(words $(SRCS_BONUS)))

set_main_count:
	$(eval FILES_COUNT := $(words $(SRCS)))

.PHONY: all clean fclean re bonus bonus_in
