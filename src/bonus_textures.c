/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 02:44:22 by dpaulino          #+#    #+#             */
/*   Updated: 2023/01/04 15:51:53 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	import_bonus_textures(t_data *data)
{
	int			i;
	char		**fnames;
	int			nb_textures;
	t_img_data	*t;

	i = 0;
	fnames = ft_split(BONUS_TEXTURES_SOLIDS, ',');
	nb_textures = ft_matrixlen(fnames);
	data->bonus_textures = malloc(sizeof(t_img_data) * nb_textures + 1);
	while (i < nb_textures)
	{
		t = &data->bonus_textures[i];
		load_images(data, t, fnames[i]);
		if (!t->img)
			exit_msg(data, "[import_textures] Pb loading xpm file", 1);
		i++;
	}
	ft_free_split(&fnames);
}
