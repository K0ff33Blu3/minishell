/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 17:37:32 by miricci           #+#    #+#             */
/*   Updated: 2025/11/28 22:48:55 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*rm_quotes(char *str)
{
	int		i;
	int		j;
	char	quote;
	char	*no_quote;

	i = 0;
	j = 0;
	no_quote = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!no_quote)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				no_quote[j++] = str[i++];
			if (str[i] == quote)
				i++;
		}
		else
			no_quote[j++] = str[i++];
	}
	no_quote[j] = 0;
	return (no_quote);
}

char	**remove_quotes(char **str)
{
	int		i;
	char	**no_quotes;

	no_quotes = malloc(sizeof(char *) * (array_size((void **)str) + 1));
	if (!no_quotes)
		return (NULL);
	i = 0;
	while (str[i])
	{
		no_quotes[i] = rm_quotes(str[i]);
		i++;
	}
	no_quotes[i] = NULL;
	return (ft_free((void **)str, -1), no_quotes);
}
