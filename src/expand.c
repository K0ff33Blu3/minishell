/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 11:40:06 by miricci           #+#    #+#             */
/*   Updated: 2025/10/10 13:33:56 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_var_in_quotes(char *quote)
{
	int		len;
	int		start;
	char	*pos;
	char	*value;
	char	*var;

	pos = ft_strchr(quote, '$') + 1;
	start = pos - quote;
	len = word_len(quote, start);
	var = ft_substr(quote, start, len);
	if (ft_strncmp(var, "?", 2) == 0)
		return (ft_itoa(g_exit_status));
	if (!var)
		return (NULL);
	value = getenv(var);
	if (value)
		return (free(var), ft_strdup(value));
	return (var);
}

char	*expand_var(char *var)
{
	char	*name_var;
	char	*value;

	if (ft_strncmp(var, "$?", 3) == 0)
		return (ft_itoa(g_exit_status));
	name_var = var + 1;
	value = getenv(name_var);
	if (value)
		return (ft_strdup(value));
	return (ft_strdup(var));
}

char	*expanded_quote(char *quote)
{
	char	*start_str;
	char	*partial_str;
	char	*final_str;
	int	start_quote;
	// char	*end_str;
	char	*value;

	start_quote = ft_strchr(quote, '$') - quote;
	start_str = ft_substr(quote, 0, start_quote);
	value = expand_var_in_quotes(quote);
	partial_str = ft_strjoin(start_str, value);
	// end_str = ft_strchr(quote, '$') + word_len(quote, start_quote);
	final_str = ft_strjoin(partial_str, (ft_strchr(quote, '$') + word_len(quote, start_quote)));
	free(value);
	free(start_str);
	free(partial_str);
	return (final_str);
}

char	**expand_env_var(char **token)
{
	int		i;
	char	**expanded_token;

	i = 0;
	expanded_token = malloc(sizeof(char *) * (array_size((void **)token) + 1));
	if (!expanded_token)
		return (NULL);
	while (token[i])
	{
		if (ft_strchr(token[i], '$'))
		{
			if (*token[i] == '\'')
				expanded_token[i] = ft_strdup(token[i]);
			else if (*token[i] == '\"')
				expanded_token[i] = expanded_quote(token[i]);
			else
				expanded_token[i] = expand_var(token[i]);
		}
		else
			expanded_token[i] = ft_strdup(token[i]);
		i++;
	}
	expanded_token[i] = NULL;
	return (ft_free((void **)token, -1), expanded_token);
}
