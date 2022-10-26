/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_ft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:17:56 by supersko          #+#    #+#             */
/*   Updated: 2022/10/26 15:09:41 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_pers( t_data *data)
{
	fprintf(stderr, "[Pers]	pos_map: [%5d,%5d]\n", data->p->pos_map.x, data->p->pos_map.y);
	fprintf(stderr, "[Pers]	pos_box: [%5d,%5d]\n", data->p->pos_box.x, data->p->pos_box.y);
	fprintf(stderr, "[Pers]	dir: 	 [%5d,%5d]\n", data->p->dir.x, data->p->dir.y);
	fprintf(stderr, "[Pers]	plane: 	 [%5d,%5d]\n", data->p->plane.x, data->p->plane.y);
}

void	print_params( t_data *data)
{
	fprintf(stderr, "[img]	ceiling_color: [%d]\n", data->i->ceiling_color);
	fprintf(stderr, "[img]	floor_color: [%d]\n", data->i->floor_color);
	fprintf(stderr, "[img]	texture NO: [%s]\n", data->i->texture_path[NO]);
	fprintf(stderr, "[img]	texture SO: [%s]\n", data->i->texture_path[SO]);
	fprintf(stderr, "[img]	texture EA: [%s]\n", data->i->texture_path[EA]);
	fprintf(stderr, "[img]	texture WE: [%s]\n", data->i->texture_path[WE]);
}

void	print_map( t_data *data)
{
	print_tab(data->map);
}

void	print_s( t_data *data)
{
	print_pers( data);
	print_params( data);
	print_map( data);
}

