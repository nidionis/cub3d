# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pwolff <pwolff@student.42mulhouse.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/04 12:25:59 by pwolff            #+#    #+#              #
#    Updated: 2022/10/10 14:52:22 by pwolff           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# New version 221004

BLU			= \033[0;34m
GRN			= \033[0;32m
RED			= \033[0;31m
RST			= \033[0m
END			= \e[0m

SRC		= srcs/hello.c

NAME		= cub3D
OBJ			= $(SRC:.c=.o)
PROJECT_H	= include/cub3d.h
CC			= gcc
FLAGS		= -Wall -Wextra -Werror
OBJS_DIR	= objs/
OBJECTS_PREFIXED = $(addprefix $(OBJS_DIR), $(OBJ))

ifeq ($(DESKTOP_SESSION), ubuntu)
MINILIBX = mlx_linux
MLXFLAGS = -I /usr/X11/include -g -Lmlx_linux -lmlx_Linux -L /usr/lib -Imlx_linux -lmlx -lXext -lX11 -lm
else
MINILIBX = minilibx_mac
MLXFLAGS = -framework OpenGL -framework AppKit
endif

$(OBJS_DIR)%.o : %.c $(PROJECT_H)
	mkdir -p $(OBJS_DIR)
	mkdir -p $(OBJS_DIR)srcs
	$(CC) $(FLAGS) -I/usr/include -I$(MINILIBX) -O3 -c $< -o $@
	printf	"\033[2K\r${BLU}[BUILD]${RST} '$<' $(END)"

$(NAME): $(OBJECTS_PREFIXED) maker
	$(CC) -o $(NAME) $(OBJECTS_PREFIXED) $(FLAGS) ./$(MINILIBX)/libmlx.a ${MLXFLAGS}
	printf "\033[2K\r\033[0;32m[END]\033[0m $(NAME)$(END)\n"

all: $(NAME)

test: all
	./$(NAME) map.cub 
	#valgrind ./$(NAME) map.cub 

maker:
	make -C ./$(MINILIBX)

clean:
	@make clean -C ./$(MINILIBX)
	@rm -rf $(OBJS_DIR)
	@printf "\033[2K\r${GRN}[CLEAN]${RST} done$(END) \n"

fclean: clean
	@rm -rf $(NAME)
	@printf "\033[2K\r${GRN}[FCLEAN]${RST} done$(END) \n"

re: fclean all 

bonus: all
	./$(NAME) map_star.cub 
	#valgrind ./$(NAME) map.cub 


.PHONY:		all clean fclean re maker test bonus
