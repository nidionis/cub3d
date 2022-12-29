SHELL      := /bin/sh
CC         := gcc
CFLAGS     := -Wall -Wextra -g -O2
INCLUDE    := -I./include -I./libft/include -I./libmlx -I./libsdl2 -fsanitize=address
NAME       := cub3D
LIBFT      := ./libft/libft.a
LIBMLX     := ./libmlx/libmlx.a
LIBS       := -L./libft -lft -L./libmlx -lmlx -L/usr/lib -lXext -lX11 -lm -lz -lSDL2
SRCDIR     := src
OBJDIR     := .obj
DEPDIR     := .dep

SRCS       := src/bonus_raycasting.c src/check_path_switch.c src/draw_line_utils.c src/get_next_line_utils.c src/load_window.c \
src/move_to_corner.c src/player_init.c src/soundtracks.c src/bonus_render2.c src/cub3d_render.c src/end_game.c src/key_event.c \
src/main.c src/parse_check_map.c src/pos_update.c src/str_ft.c src/bonus_render.c src/draw_compass.c src/exit_ft.c src/keys_game.c \
src/map_ft.c src/parse_file_colors.c src/raycasting.c src/bonus_textures.c src/draw_functions2.c src/free_functions.c src/keys_menu.c \
src/matrix.c src/parse_format_map.c src/raycasting_utils.c src/utils.c src/camera_ft.c src/draw_functions.c src/ft_list.c \
src/keys_resolution.c src/mouse.c src/parse_import.c src/ray_set_distances.c src/vector_ft.c src/check_path_door.c src/draw_interface.c \
src/generate_map.c src/keys_settings.c src/move_crossing_box.c src/parse_init.c src/render_menu.c src/check_path_map.c src/draw_line.c \
src/get_next_line.c src/load_menu.c src/move_player.c src/parse_params.c src/rotate_player.c src/utils2.c src/game_event.c
OBJS       := $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

LGREEN     := \033[1;32m
WHITE      := \033[1;37m
NOC        := \033[0m

linux: $(NAME)
$(NAME): $(OBJS) $(LIBFT) $(LIBMLX)
	@echo -e "$(LGREEN)Linking executable $(NAME)$(NOC)"
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) $(LIBS) -o $@
	@echo -e "Built target $(NAME)"
.PHONY: linux

all:
	@$(MAKE) fclean
	@git checkout -f master
	@$(MAKE)
.PHONY: all

# bonus:
# 	@$(MAKE) fclean
# 	@git checkout -f bonus
# 	@$(MAKE)
# .PHONY: bonus

$(LIBFT): NONE
	@$(MAKE) -C ./libft
$(LIBMLX): NONE
	@$(MAKE) -C ./libmlx MAKEFLAGS= -j 1
.PHONY: NONE

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPDIR)/%.d | $(OBJDIR) $(DEPDIR)
	$(CC) $(CFLAGS) $(INCLUDE) -MMD -MF $(DEPDIR)/$*.tmp -c $< -o $@
	@$(POST_COMPILE)
$(OBJDIR):
	@mkdir -p $(OBJDIR)
$(DEPDIR):
	@mkdir -p $(DEPDIR)
$(DEPDIR)/%.d: ;
.PRECIOUS: $(DEPDIR)/%.d

clean:
	@$(MAKE) -C ./libft clean
	@$(MAKE) -C ./libmlx clean
	@echo -e "$(WHITE)Removing C object files...$(NOC)"
	@-rm -rf $(OBJDIR)
	@echo -e "$(WHITE)Removing make dependency files...$(NOC)"
	@-rm -rf $(DEPDIR)
.PHONY: clean

fclean: clean
	@$(MAKE) -C ./libft fclean
	@-rm -f libmlx.a
	@echo -e "$(WHITE)Removing executable $(NAME)$(NOC)"
	@-rm -f $(NAME)
.PHONY: fclean

re:
	$(MAKE) fclean
	$(MAKE) linux
.PHONY: re
