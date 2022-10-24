BLU			= \033[0;34m
GRN			= \033[0;32m
RED			= \033[0;31m
RST			= \033[0m
END			= \e[0m

SRCDIR   = src
OBJDIR   = obj

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

ifeq ($(DESKTOP_SESSION), ubuntu)
MINILIBX = mlx_linux
MLXFLAGS = -I /usr/X11/include -g -Lmlx_linux -lmlx_Linux -L /usr/lib -Imlx_linux -lmlx -lXext -lX11 -lm
else
MINILIBX = minilibx_mac
MLXFLAGS = -framework OpenGL -framework AppKit
endif

all: $(NAME)

$(NAME): $(OBJECTS) maker
	$(CC) $(OBJECTS) $(CFLAGS) $(LIBFT) ./$(MINILIBX)/libmlx.a ${MLXFLAGS} -o $(NAME) 

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -I/usr/include -I./include -I$(LIBFT_DIR) -I$(MINILIBX) -O3 -c $< -o $@

maker:
	make -C ./$(MINILIBX)
	make -C ./$(LIBFT_DIR)

clean:
	@make clean -C ./$(MINILIBX)
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -rf $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@make -C $(MINILIBX) fclean

re: fclean all 

.PHONY:		all clean fclean re maker test bonus
