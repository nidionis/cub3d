/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_ft.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:17:56 by supersko          #+#    #+#             */
/*   Updated: 2022/10/26 15:53:14 by supersko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**get_identifiers_ls(int identifier_len)
{
	char	**identifiers;

	identifiers = NULL;
	if (identifier_len == 2)
		identifiers = ft_split("NO ,SO ,WE ,EA ", ',');
	else if (identifier_len == 1)
		identifiers = ft_split("F ,C ", ',');
	return (identifiers);
}

static int	refresh_ret_if_is_param(char **identifiers, \
		int *returned, int *i, char *str)
{
	while (is_blank_char(*str))
		str++;
	if (!ft_strncmp(identifiers[*i], str, ft_strlen(identifiers[*i])))
	{
		*returned = *i;
		return (1);
	}
	(*i)++;
	return (0);
}

int	conv_id_param(t_data *data, int identifier_len, char *str)
{
	int		i;
	int		returned;
	char	**identifiers;

	returned = -1;
	i = 0;
	identifiers = get_identifiers_ls(identifier_len);
	if (identifiers)
		while (identifiers[i])
			if (refresh_ret_if_is_param(identifiers, &returned, &i, str))
				break ;
	ft_free_split(&identifiers);
	if (returned == -1)
		exit_msg(data, "[conv_id_param] wrong param identifier\n", -1);
	if (identifier_len == 1)
		returned += 4;
	return (returned);
}

int	get_identifier(t_data *data, char *str)
{
	int		identifier_len;

	identifier_len = ft_strlen_char(str, ' ');
	if (is_map_line(data, str))
		return (11);
	if (identifier_len > 3 || identifier_len < 2)
		exit_msg(data, "[get_identifier] wrong param identifier", -1);
	return (conv_id_param(data, identifier_len, str));
}
