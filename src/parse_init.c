/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suplayerko <suplayerko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:17:56 by suplayerko          #+#    #+#             */
/*   Updated: 2022/11/13 15:22:00 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//init map, textures, sprites as null and ceiling/floor as -1
void	init_null(t_data *data, int *map_parse)
{
	int	i;

	*map_parse = 0;
	data->map = NULL;
	i = 0;
	while (i < (int)NB_TEXTURES)
	{
		data->image->texture_path[i] = NULL;
		i++;
	}
	data->image->floor_color = -1;
	data->image->ceiling_color = -1;
}


//open file
void	init_fd(t_data *data, int *fd, char *fname)
{
	file_extention_available(data, fname);
	(*fd) = open(fname, O_RDONLY);
	if ((*fd) == -1)
		exit_msg(data, "[init_fd] Error opening file (check file name or chmod)", -1);
}

//verify extension file
void	file_extention_available(t_data *data, char *fname)
{
	char	*p_ext;

	if (fname)
	{
		p_ext = ft_strnstr(fname, ".cub", ft_strlen(fname));
		if (ft_strlen_char(p_ext, ' ') == 4)
			return ;
	}
	exit_msg(data, "[file_extention_available] only .cub extension", -1);
}

void	init_player(t_data *data, int x, int y, int *is_player)
{
	char	c;

	c = data->map[y][x];
	if (c == NORTH_CHAR)
	{
		data->player->direction.x = 0;
		data->player->direction.y = -1;
	}
	if (c == SOUTH_CHAR)
	{
		data->player->direction.x = 0;
		data->player->direction.y = 1;
	}
	if (c == EAST_CHAR)
	{
		data->player->direction.x = 1;
		data->player->direction.y = 0;
	}
	if (c == WEST_CHAR)
	{
		data->player->direction.x = -1;
		data->player->direction.y = 0;
	}
	data->player->pos_map.x = x;
	data->player->pos_map.y = y;
	data->player->pos_box.x = UNITS_PER_BOX / 2;
	data->player->pos_box.y = UNITS_PER_BOX / 2;
	data->player->pos_in_step = update_pos_in_step(data->player);
	data->player->pos_in_pix = update_pos_in_pix(data->player);
	data->player->speed = 0;
	data->player->stamina = 100;
	//devine plnan
	(*is_player)++;
}
