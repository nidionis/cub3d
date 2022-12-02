BLU			= \033[0;34m
GRN			= \033[0;32m
RED			= \033[0;31m
RST			= \033[0m
END			= \e[0m

SRCDIR   = src
OBJDIR   = obj
DEBUG_LOG_FILE = debug_file

SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

NAME		= cub3D
OBJ			= $(SRC:.c=.o)
LIBFT_DIR 	= libft
PROJECT_H	= include/cub3d.h $(LIBFT_DIR)/libft.h
CC			= gcc
LINKER   	= gcc
CFLAGS		= -Wall -Wextra -Werror -g3
LIBFT 		= $(LIBFT_DIR)/libft.a

ifeq ($(DESKTOP_SESSION), qtile)
MINILIBX = minilibx_linux
MLXFLAGS = -I /usr/X11/include -g -Lminilibx_linux -L /usr/lib -Iminilibx_linux -lmlx -lXext -lX11 -lm
else
MINILIBX = minilibx_mac
MLXFLAGS = -lmlx -framework OpenGL -framework AppKit
PROJECT_H += $(MINILIBX)/mlx_new_window.h $(MINILIBX)/mlx.h $(MINILIBX)/mlx_int.h $(MINILIBX)/mlx_new_window.h $(MINILIBX)/mlx_opengl.h $(MINILIBX)/mlx_png.h
endif

all: $(NAME)

$(NAME): $(OBJECTS) maker
	$(CC) $(OBJECTS) $(CFLAGS) ${MLXFLAGS} $(LIBFT) ./$(MINILIBX)/libmlx.a -o $(NAME) 
	@rm -rf $(DEBUG_LOG_FILE)

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -I/usr/include -I./include -I$(LIBFT_DIR) -I$(MINILIBX) -O0 -c $< -o $@

maker:
	make -C ./$(MINILIBX)
	make -C ./$(LIBFT_DIR)

clean:
	@make -C ./$(MINILIBX) clean
	@make -C $(LIBFT_DIR) fclean
	@rm -rf $(OBJDIR)
	@rm -rf $(DEBUG_LOG_FILE)

fclean: clean
	@rm -rf $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@make -C $(MINILIBX) clean # because no rules fclean

re: fclean all 

.PHONY:		all clean fclean re maker test bonus
