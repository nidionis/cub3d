/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 02:41:23 by dpaulino          #+#    #+#             */
/*   Updated: 2023/01/02 11:06:09 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	get_res_height(void)
{
	int	height;

	height = 0;
	if (g_status == 0)
		height = SCREEN_HEIGHT;
	else if (g_status == 1)
		height = 1080;
	else if (g_status == 2)
		height = 700;
	else if (g_status == 3)
		height = 500;
	return (height);
}

int	get_res_width(void)
{
	int	width;

	width = 0;
	if (g_status == 0)
		width = SCREEN_WIDTH;
	else if (g_status == 1)
		width = 1900;
	else if (g_status == 2)
		width = 1200;
	else if (g_status == 3)
		width = 700;
	return (width);
}
