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
PROJECT_H	= include/cub3d.h
CC			= gcc
LINKER   = gcc
CFLAGS		= -Wall -Wextra -Werror

ifeq ($(DESKTOP_SESSION), ubuntu)
MINILIBX = mlx_linux
MLXFLAGS = -I /usr/X11/include -g -Lmlx_linux -lmlx_Linux -L /usr/lib -Imlx_linux -lmlx -lXext -lX11 -lm
else
MINILIBX = minilibx_mac
MLXFLAGS = -framework OpenGL -framework AppKit
endif

all: $(NAME)

$(NAME): $(OBJECTS) maker
	$(CC) $(OBJECTS) $(CFLAGS) ./$(MINILIBX)/libmlx.a ${MLXFLAGS} -o $(NAME) 

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -I/usr/include -I./include -I$(MINILIBX) -O3 -c $< -o $@

test: all
	./$(NAME) map.cub 
	#valgrind ./$(NAME) map.cub 

maker:
	make -C ./$(MINILIBX)

clean:
	@make clean -C ./$(MINILIBX)
	@rm -rf $(OBJDIR)
	@printf "\033[2K\r${GRN}[CLEAN]${RST} done$(END) \n"

fclean: clean
	@rm -rf $(NAME)
	@printf "\033[2K\r${GRN}[FCLEAN]${RST} done$(END) \n"

re: fclean all 

bonus: all
	./$(NAME) map_star.cub 
	#valgrind ./$(NAME) map.cub 


.PHONY:		all clean fclean re maker test bonus
