/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 13:09:34 by supersko          #+#    #+#             */
/*   Updated: 2022/05/31 18:40:46 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	error_msg(char *msg)
{
	int	len;

	len = 0;
	while (msg[len])
		len++;
	if (!msg)
		write(2, "Error\n", 6);
	else
		write(2, msg, len);
	exit (-1);
}
