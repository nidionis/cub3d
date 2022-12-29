/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_ft.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:17:56 by supersko          #+#    #+#             */
/*   Updated: 2022/12/29 14:01:20 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	is_map_line(t_data *data, char *str)
{
	if (str)
	{
		if (is_blank_line(str))
			return (0);
		while (*str != '\n' && *str != '\0')
		{
			if (!(is_mapcase(data, *str) || is_cardinal(*str)))
				return (0);
			str++;
		}
		return (1);
	}
	else
		return (-1);
}

int	is_blank_char(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	else
		return (0);
}

int	is_blank_line(char *line)
{
	while (*line)
	{
		if (!is_blank_char(*line++))
			return (0);
	}
	return (1);
}
