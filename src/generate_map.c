/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:14:23 by dpaulino          #+#    #+#             */
/*   Updated: 2022/12/12 11:33:21 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	generate_map(t_data *data)
{
	int y;
	int x;
	int random;

	x = 2;
	y = 2;
	while (data->map[y] && y != data->map_height - 2)
	{
		while (data->map[y][x] && x != data->map_width - 2)
		{
			random = rand() % 2;
			if (data->map[y][x] != 'E' && data->map[y][x] != '2')
			{
				if (random == 1)
					data->map[y][x] = '1';
				else if (random == 0)
					data->map[y][x] = '0';
			}
			x++;
		}
		x = 2;
		y++;
	}
	return (1);
}

char **alloc_mem(int size_y, int size_x)
{
	int i;
	char **map;
	i = 0;
	map = malloc(sizeof(char *) * (size_y));
	while (i < size_y)
	{
		map[i] = malloc(sizeof(char) * (size_x));
		i++;
	}
	return (map);
}

void	draw_map_border(t_data *data, int size_y, int size_x)
{
	char	**new_map;
	t_point old;
	t_point new;

	new_map = NULL;
	new.x = 0;
	new.y = 0;
	old.x = 0;
	old.y = 0;
	new_map = alloc_mem(size_y + 2, size_x + 2);
	while (new.y < size_y + 2)
	{
		while (new.x < size_x + 2)
		{
			if (new.x == 0 || new.y == 0 || new.x == size_x + 1 || new.y == size_y + 1)
				new_map[new.y][new.x] = '1';
			else
			{
				if (data->map[old.y][old.x] == ' ')
					new_map[new.y][new.x] = '1';
				else
					new_map[new.y][new.x] = data->map[old.y][old.x];
				old.x++;
			}
			new.x++;
		}
		new_map[new.y][new.x] = '\0';
		printf("%s\n",new_map[new.y]);
		if (new.y != 0 && new.y != size_y + 1)
			old.y++;
		new.y++;
		new.x = 0;
		old.x = 0;
	}
	new_map[new.y] = NULL;
	data->map = new_map;
}