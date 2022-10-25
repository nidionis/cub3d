/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_ft.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <ndionis@student.42mulhouse.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:17:56 by supersko          #+#    #+#             */
/*   Updated: 2022/10/25 14:12:11 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clean_exit(t_s *s, int exit_code)
{
	int	i;

	if (s)
	{
		if (s->line)
			free(s->line);
		if (s->line_split)
			ft_free_split(&s->line_split);
		if (s->map)
			ft_free_split(&s->map);
		if (s->p)
			free(s->p);
		if (s->i)
		{
			i = 0;
			while (i < NB_TEXTURES)
			{
				if (s->i->texture_path[i])
					free(s->i->texture_path[i++]);
			}
			free(s->i);
		}
		free(s);
	}
	exit(exit_code);
}

void	exit_msg(t_s *s, char *msg, int ret_exit)
{
	error_msg(msg);
	clean_exit(s, ret_exit);
}
