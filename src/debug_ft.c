/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <ndionis@student.42mulhouse.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:17:56 by supersko          #+#    #+#             */
/*   Updated: 2022/10/25 20:48:37 by supersko         ###   ########.fr       */
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
