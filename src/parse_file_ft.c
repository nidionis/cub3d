/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_ft.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:17:56 by supersko          #+#    #+#             */
/*   Updated: 2022/10/26 15:09:41 by supersko         ###   ########.fr       */
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
		int *ret, int *i, char *str)
{
	if (!ft_strncmp(identifiers[*i], str, ft_strlen(identifiers[*i])))
	{
		*ret = *i;
		return (1);
	}
	(*i)++;
	return (0);
}

int	conv_id_param( t_data *data, int identifier_len, char *str)
{
	int		i;
	int		ret;
	char	**identifiers;

	ret = -1;
	i = 0;
	identifiers = get_identifiers_ls(identifier_len);
	if (identifiers)
		while (identifiers[i])
			if (refresh_ret_if_is_param(identifiers, &ret, &i, str))
				break ;
	ft_free_split(&identifiers);
	if (ret == -1)
		exit_msg( data, "[conv_id_param] wrong param identifier\n", -1);
	if (identifier_len == 1)
		ret += 4;
	return (ret);
}

int	get_identifier( t_data *data, char *str)
{
	int		identifier_len;

	identifier_len = ft_strlen_char(str, ' ');
	if (is_map_line(str))
		return (11);
	if (identifier_len > 2 || identifier_len < 1)
		exit_msg( data, "[get_identifier] wrong param identifier", -1);
	return (conv_id_param( data, identifier_len, str));
}
