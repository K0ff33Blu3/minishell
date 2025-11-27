/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elmondo <elmondo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:03:04 by miricci           #+#    #+#             */
/*   Updated: 2025/11/27 17:27:40 by elmondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*rm_quotes(char *str)
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

static int	count_redir(char **token)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (token[i])
	{
		if (!is_redir(token, i))
			count++;
		i++;
	}
	return (count);
}

char	**parse_cmd_args(char **token, int *exit_status)
{
	int		i;
	int		j;
	int		arg_size;
	char	**arg;

	arg_size = array_size((void **)token) - (count_redir(token) * 2);
	arg = malloc(sizeof(char *) * (arg_size + 1));
	i = 0;
	j = 0;
	while (token[i])
	{
		if (!is_redir(token, i))
			i += 2;
		else if (is_redir(token, i) == SYNT_ERR)
		{
			*exit_status = SYNT_ERR;
			ft_perror(token[i + 1], *exit_status);
			return (ft_free((void **)arg, j), NULL);
		}
		else
			arg[j++] = ft_strdup(token[i++]);
	}
	arg[j] = NULL;
	return (arg);
}

char	**get_cmd_token(char **all_token, int start, int end)
{
	char	**result;
	int		i;

	result = (char **)malloc(sizeof(char *) * (end - start + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (start < end)
	{
		result[i] = ft_strdup(all_token[start]);
		start++;
		i++;
	}
	result[i] = NULL;
	return (result);
}
