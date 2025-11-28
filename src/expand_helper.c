/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 17:32:48 by elmondo           #+#    #+#             */
/*   Updated: 2025/11/28 23:26:02 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	get_kind_of_quote(char *str)
{
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
			return (*str);
		str++;
	}
	return (0);
}

int	find_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] != '$' && str[i] != '\\'))
	{
		if (str[i] == '\'')
			i = skip_quote(str, i);
		else
			i++;
	}
	return (i);
}
