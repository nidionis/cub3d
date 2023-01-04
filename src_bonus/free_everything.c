/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_everything.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 17:07:56 by dpaulino          #+#    #+#             */
/*   Updated: 2023/01/04 17:08:09 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub3d_bonus.h"

void	free_everything(t_data *data)
{
	mlx_destroy_image(data->window->mlx, data->img->img);
	free(data->key_status);
	free_bonus_textures(data);
	free_menu(data);
	free(data->img);
	ft_free_split(&data->map);
	free_texture_path(data);
	free_wall_textures(data);
	mlx_destroy_window(data->window->mlx, data->window->init);
	free(data->window->mlx);
	free_data(data);
	free(data);
}
