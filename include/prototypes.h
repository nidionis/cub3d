/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 13:41:57 by dpaulino          #+#    #+#             */
/*   Updated: 2022/12/08 16:16:49 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H
# include "cub3d.h"

void			error_msg(char *msg);
char			**default_map(char	*argv[]);
char			**ft_append_tab(char **matrix, char *str);
char			*get_next_line(int fd);
int				func(void);
int				conv_id_param(t_data *data, int identifier_len, char *str);
void			file_extention_available(t_data *data, char *fname);
int				ft_matrixlen(char **matrix);
int				get_identifier(t_data *data, char *str);
int				import_params(t_data *data);
void			parse_file(char *fname, t_data	*s);
int				parsing_loop(t_data *data, int *map_parse);
t_player		*default_player(void);
t_point			get_vector(t_point *from, t_point *to);
t_vector		vec_diff(t_vector v1, t_point v2);
t_vector		vec_scale(t_vector vec, double scale);
void			init_null(t_data *data, int *map_parse);
void			add_vec(t_point	*pt, t_point vec);
void			clean_exit(t_data *data, int exit_code);
void			exit_msg(t_data *data, char *msg, int ret_exit);
void			import_param(t_data *data, int identifier, char *line);
void			ray_parse(t_data *data);
void			wrong_color(t_data *data, char *color_strimed);
int				is_blank_line(char *line);
int				is_blank_char(char c);
int				is_map_line(t_data *data, char *str);
int				check_map(t_data *data);
unsigned int	init_f_c_color(t_data *s, char *line);
void			print_player(t_data *data, int fd);
void			print_params(t_data *data, int fd);
void			print_map(t_data *data, int fd);
void			print_s(t_data *data, int fd);
void			redir_debug_file_logs(t_data *data, char *fname, int log_type);
void			init_player(t_data *data, int x, int y, int *is_player);
void			init_fd(t_data *data, int *fd, char *fname);
int				check_wall(t_data *data, int crossover_direction);
int				check_update_box_pos(t_data *data);
int				move_player(t_data *data, int direction);
t_point			translate_pt_inplace(t_vector vector, t_point *pt);
double			distance_point_to_vector(t_point point, t_point v_p1, \
t_point v_p2);
t_point			make_point(int x, int y);
int				north_crossing(t_data *data);
int				south_crossing(t_data *data);
int				east_crossing(t_data *data);
int				west_crossing(t_data *data);
void			rotate_vector(t_vector *vector, double radian_angle);
double			degree_to_radian(double degree_angle);
int				corner_crossing(t_data *data);
int				is_block(t_data *data, char c);
void			redir_debug_file_msg(char *fname, char *msg);
void			rotate_player(t_player *player, int move);
int				is_available_mapcase(t_data *data, int x, int y, \
int *is_player);
int				is_block(t_data *data, char c);
int				is_mapcase(t_data *data, char c);
int				is_NSEW(char c);
void			init_cam_vector(t_data *data);
t_point			get_player_absolute_position(t_player *player);
void			clean_useless_empty_splace(char	**map);
void			rectangle_map(t_data *data, char **map);
void			format_map(t_data *data);
unsigned int	rgb_conv(int R, int G, int B);
void			translate_vector_as_pt(t_vector vector, t_vector *pt);
t_point			update_pos_in_pix(t_player *player);
t_point			update_pos_in_step(t_player *player);
void			init_cam_vector(t_data *data);
void			set_camera(t_data *data);
double			vec_len(t_vector vector);
t_vector		convert_pt_to_vec(t_point p);
void			set_delta_distance(t_data *data);
void			set_side_distance(t_data *data);
char			pix_pos_to_map_case(t_data *data, t_point absolute_pos);
void			draw_wall_line(t_data *data, int i);
int				ray_cast(t_data *data);
void			set_arRay(t_data *data);
int				still_in_map(t_data *data, t_point pt);
double			distance_line_to_point(t_vector line[2], t_point p);
void			set_delta_distance(t_data *data);
void			set_side_distance(t_data *data);
t_point			translate_pt(t_vector vector, t_point pt);
int	    ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
double			distance_points(t_point p1, t_point p2);
void			convert_pos_and_dir_to_line(t_point pos, t_vector vec, t_vector line[2]);
int				ft_lstlen(t_list *lst);
t_list		*sort_obstacles(t_list **ls);
int				get_side_hit(t_data *data, int index_closest);
int				len_overflow(int len);
void			set_beam(t_data *data, t_list **obstacles_ls);
double			get_dist_from_plan(t_data *data, t_rayponse *rayponse);
t_point			units_pos_to_minimap_pos(t_data *data, t_point absolute_position);
int				load_window(t_data *data);
int				minimap_render(t_data *data);
int				player_init(char **map, t_player *player);
int				exit_game(t_data *data);
int				graphics_render(t_data *data);
int				cub3d_render(t_data *data);

//___________________draw functions_______________
void			draw_line(t_data *data, t_point	*start, t_point	*end, int color);
void			draw_mini_map(t_data *data);
void			draw_player(t_data *data);
void			draw_vision_field(t_data *data, t_point minimap_position);
void    		my_mlx_pixel_put(t_img_data *img, int x, int y, unsigned int color);
void			init_key_status(t_data *data);
int     		key_press(int key, t_data *data);
int     		key_realese(int key, t_data *data);
void			load_textures(t_data *data);
void			draw_cube(t_data *data, int size, int pos_y, int pos_x, int color);
void			load_menu(t_data *data);
int				load_images(t_data *data, t_img_data *image, char *path);
int    			render_menu(t_data *data);
void			draw_image(t_img_data *img1, t_img_data *img2, t_point pos, int color);
void			player_smoth_move(t_data *data);
t_point			y_x(int y, int x);
void			settings_key_press(int key, t_data *data);
void			clear_img(t_img_data *img);
int				key_game(int key, t_data *data);
void			menu_key_press(int key, t_data *data);
void			resolution_key_press(int key, t_data *data);
void	draw_line_textured(t_data *data, t_point start, t_point end, int line_height, t_rayponse *ray);
void	draw_wall_textured(t_data *data, int i_ray);
void	draw_ceiling_floor_mandatory(t_data *data);
int	f_is_box_crossed(t_player *player);
t_point	map_position_in_front_of_player(t_player *player);
void    generate_map_content(t_data *data, char c);
int	check_path(t_data *data, int row, int col);
int	generate_map(t_data *data);

t_point get_img_size(char *path);

//proto nico

void	import_bonus_textures(t_data *data);
void	import_sprites_textures(t_data *data);
int	get_wallX(t_rayponse *ray);
t_list	*sort_obstacles(t_list **lst);
void	add_obstacle(t_data *data, t_rayponse ray, char map_case, int dir, t_list **obstacles_ls);
void add_sprites_to_obstacles_ls(t_data *data, t_list **obstacles_ls);
t_list		*add_sprites(t_data *data, t_rayponse *rayturned, t_list **obstacles_ls);
void	clean_obstacle_behind_wall(t_list **list, double distance_max);
t_list *init_random_sprites(t_data *data);
#endif
