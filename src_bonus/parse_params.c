/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:17:56 by supersko          #+#    #+#             */
/*   Updated: 2023/01/02 12:57:15 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub3d_bonus.h"

/* the params are converted in int to facilitate parsing */
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

/* return true if is param, used in conv_id_param  */
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
	if ((int)ft_strlen_char(str, '\t') < identifier_len)
		identifier_len = ft_strlen_char(str, ' ');
	if (is_map_line(data, str))
		return (11);
	if (identifier_len > 2 || identifier_len < 1)
		exit_msg(data, "[get_identifier] wrong param identifier", -1);
	return (conv_id_param(data, identifier_len, str));
}
