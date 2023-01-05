/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_ft.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:17:56 by supersko          #+#    #+#             */
/*   Updated: 2023/01/04 17:42:42 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/* where all pointers are cleaned, especially in a emergency exit */
void	clean_exit(t_data *data, int exit_code)
{
	if (data)
	{
		if (data->image)
			free(data->image);
		if (data->player)
			free(data->player);
		if (data->map)
			ft_free_split(&data->map);
		if (data->blocks)
			free(data->blocks);
		if (data->map_cases)
			free(data->map_cases);
		if (data->cam)
		{
			if (data->cam->beam)
				free(data->cam->beam);
			free(data->cam);
		}
		free(data);
	}
	exit(exit_code);
}

void	exit_msg(t_data *data, char *msg, int ret_exit)
{
	error_msg(msg);
	clean_exit(data, ret_exit);
}

int	exit_game(t_data *data)
{
	free_everything(data);
	exit(0);
}
