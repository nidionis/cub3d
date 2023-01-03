/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_border.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 10:50:21 by dpaulino          #+#    #+#             */
/*   Updated: 2023/01/03 10:50:56 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub3d_bonus.h"

void	init_new_old_map(t_point *new, t_point *old)
{
	new->x = 0;
	new->y = 0;
	old->x = 0;
	old->y = 0;
}

void	complete(t_point *new, t_point *old, int size_y)
{
	if (new->y++ != 0 && new->y != size_y + 1)
		old->y++;
	new->x = 0;
	old->x = 0;
}

void	draw_map_border(t_data *data, int size_y, int size_x)
{
	char	**new_map;
	t_point	old;
	t_point	new;

	init_new_old_map(&new, &old);
	new_map = alloc_mem(size_y + 2, size_x + 2);
	while (new.y < size_y + 2)
	{
		while (new.x < size_x + 2)
		{
			if (new.x == 0 || new.y == 0 || new.x == size_x + 1 \
			|| new.y == size_y + 1)
				new_map[new.y][new.x++] = '1';
			else
			{
				if (data->map[old.y][old.x] == ' ')
					new_map[new.y][new.x++] = '1';
				else
					new_map[new.y][new.x++] = data->map[old.y][old.x++];
			}
		}
		complete(&new, &old, size_y);
	}
	ft_free_split(&data->map);
	data->map = new_map;
}
