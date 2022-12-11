#include <cub3d.h>

void   make_sprite(t_data *data, t_point p, t_list **sprite_list)
{
       t_list          *new_item;
       t_sprite        *new_sprite;
       int             nb_types;
       char            **fnames;

       nb_types = 0;
       fnames = ft_split(SPRITES_TEXTURES, ',');
       nb_types = ft_matrixlen(fnames);
       ft_free_split(&fnames);
       new_sprite = malloc(sizeof(t_sprite));
       if (!new_sprite)
               exit_msg(data, "[make_sprite] Did not malloc",1);
       new_sprite->pos = p;
       new_sprite->type = rand() % nb_types;
       new_item = ft_lstnew((void *)new_sprite);
       if (!new_item)
               exit_msg(data, "[make_sprite] Did not malloc",1);
       ft_lstadd_front(sprite_list, new_item);
}

t_list *init_random_sprites(t_data *data)
{
       int     proba_sprite;
       t_point p;
       t_list  *sprite_list;

       proba_sprite = UNITS_PER_BOX * UNITS_PER_BOX / SPRITE_DENSITY + 1;
       p.y = 0;
       sprite_list = NULL;
       while (p.y < data->map_size_in_units[_y])
       {
               p.x = 0;
               while (p.x < data->map_size_in_units[_x])
               {
                       if (rand() % proba_sprite == 0)
                               make_sprite(data, p, &sprite_list);
		       p.x++;
               }
               p.y++;
       }
       return (sprite_list);
}

/*
void   add_sprite(t_data *data, t_sprite *sprite, double dist_to_ray, double dist_to_player, t_list **obstacles_ls)
{
       t_obstacle      *obst;
       t_list          *item;

       obst = malloc(sizeof(t_obstacle));
       if (!obst)
               exit_msg(data, "[add_obstacle] pb adding obstacle", 1);
       obst->dist = dist_to_player;
       obst->textureX = dist_to_ray;
       obst->texture = &data->sprite_textures[sprite->type];
       item = ft_lstnew((void *)obst);
       if (!item)
               exit_msg(data, "[add_obstacle] pb adding obstacle", 2);
       ft_lstadd_front(obstacles_ls, item);
}
*/

int	is_in_front_side(t_data *data, t_point p)
{
	int is_true;

	is_true = 0;
	// if sprite is on west dide
	if (data->player->pos_in_pix.x - p.x > 0)
	{
	       	if (data->player->direction.x < 0)
			is_true = 1;
	}
	if (data->player->pos_in_pix.y - p.y)
	{
	       	if (data->player->direction.y < 0)
			is_true = 1;
	}
	return (is_true);
}

void add_sprites_to_obstacles_ls(t_data *data, t_list **obstacles_ls)
{
       t_obstacle	*new_sprite;
       t_list		*sprite;
       t_list		*item;
       double		dist_to_ray;
       t_vector		line[2];

       sprite = data->image->sprite_ls;
       while (sprite)
       {
               // we should check if sprite is in front side, but who carse for grass and flowers
	       if (!is_in_front_side(data, ((t_sprite *)sprite->content)->pos))
	       {
		       sprite = sprite->next;
		       break;
	       }
               line[1] = convert_pt_to_vec(data->player->pos_in_pix);
               line[0] = convert_pt_to_vec(translate_pt(vec_scale(data->cam->beam->direction,1000), data->player->pos_in_pix));

	fprintf(stderr,"[add_sprites_to_obstacles_ls] line[0]=%lf,%lf, line[1]=%lf,%lf\n", line[0].x, line[0].y, line[1].x, line[1].y);
               dist_to_ray = distance_line_to_point(line, ((t_sprite *)sprite->content)->pos);
               if (dist_to_ray * 5 < (double)UNITS_PER_BOX )
               {
			new_sprite = malloc(sizeof(t_obstacle));
			if (!new_sprite)
				exit_msg(data, "[add_obstacle] pb adding obstacle", 1);
			new_sprite->dist = distance_points(data->player->pos_in_pix, ((t_sprite *)sprite->content)->pos);
			if (new_sprite->dist < 2)
				new_sprite->dist = 2;
               //      get textureX (probablement UNITS_PER_BOX / dist sprite/cam_plan)
			new_sprite->texture = &data->sprite_textures[((t_sprite *)sprite->content)->type];
			new_sprite->textureX = (int)dist_to_ray;// / (double)UNITS_PER_BOX));
			fprintf(stderr,"[add_sprites_to_obstacles_ls] textureX=%d\n", new_sprite->textureX);
											if (new_sprite->textureX > new_sprite->texture->line_len)
											{
												free(new_sprite);
												break;
											}
			item = ft_lstnew((void *)new_sprite);
			if (!item)
				exit_msg(data, "[add_obstacle] pb adding obstacle", 2);
			ft_lstadd_front(obstacles_ls, item);
	       }
		sprite = sprite->next;
       }
}

/*
void	add_obstacle(t_data *data, t_rayponse ray, char map_case, int dir, t_list **obstacles_ls)
{
	t_obstacle	*obst;
	t_list		*item;
	int		i_texture;
	(void)map_case;

	obst = malloc(sizeof(t_obstacle));
	if (!obst)
		exit_msg(data, "[add_obstacle] pb adding obstacle", 1);
	ray.side = get_side_hit(data, dir);
	i_texture = map_case - '2' + ray.side;
	obst->dist = get_dist_from_plan(data, &ray);
	obst->textureX = get_wallX(&ray);
	obst->texture = &data->bonus_textures[i_texture];
	item = ft_lstnew((void *)obst);
	fprintf(stderr,"[obstacle_added] i:%d\n", i_texture);
	if (!item)
		exit_msg(data, "[add_obstacle] pb adding obstacle", 2);
	ft_lstadd_front(obstacles_ls, item);
}
*/
