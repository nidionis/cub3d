/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_ft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <ndionis@student.42mulhouse.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:17:56 by supersko          #+#    #+#             */
/*   Updated: 2022/10/26 12:12:31 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_pers(t_s *s)
{
	fprintf(stderr, "[Pers]	pos_map: [%5d,%5d]\n", s->p->pos_map.x, s->p->pos_map.y);
	fprintf(stderr, "[Pers]	pos_box: [%5d,%5d]\n", s->p->pos_box.x, s->p->pos_box.y);
	fprintf(stderr, "[Pers]	dir: 	 [%5d,%5d]\n", s->p->dir.x, s->p->dir.y);
	fprintf(stderr, "[Pers]	plane: 	 [%5d,%5d]\n", s->p->plane.x, s->p->plane.y);
}

void	print_params(t_s *s)
{
	fprintf(stderr, "[img]	ceiling_color: [%d]\n", s->i->ceiling_color);
	fprintf(stderr, "[img]	floor_color: [%d]\n", s->i->floor_color);
	fprintf(stderr, "[img]	texture NO: [%s]\n", s->i->texture_path[NO]);
	fprintf(stderr, "[img]	texture SO: [%s]\n", s->i->texture_path[SO]);
	fprintf(stderr, "[img]	texture EA: [%s]\n", s->i->texture_path[EA]);
	fprintf(stderr, "[img]	texture WE: [%s]\n", s->i->texture_path[WE]);
}

void	print_map(t_s *s)
{
	print_tab(s->map);
}

void	print_s(t_s *s)
{
	print_pers(s);
	print_params(s);
	print_map(s);
}

