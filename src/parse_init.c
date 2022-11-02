/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suplayerko <suplayerko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:17:56 by suplayerko          #+#    #+#             */
/*   Updated: 2022/10/26 17:33:57 by suplayerko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_null(t_data *data, int *map_parse)
{
	int	i;

	*map_parse = 0;
	data->map = NULL;
	i = 0;
	while (i < NB_TEXTURES)
		data->image->texture_path[i++] = NULL;
	data->image->floor_color = -1;
	data->image->ceiling_color = -1;
}

void	init_fd(t_data *data, int *fd, char *fname)
{
	file_extention_available(data, fname);
	*fd = open(fname, O_RDONLY);
	if (*fd == -1)
		exit_msg(data, "[init_fd] Error opening file (check file name or chmod)", -1);
}

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
	update_pos_in_step(data->player);
	update_pos_in_pix(data->player);
	//devine plnan
	(*is_player)++;
}
