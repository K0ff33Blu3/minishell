/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 11:40:06 by miricci           #+#    #+#             */
/*   Updated: 2025/10/13 23:24:36 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*expand_var_in_quotes(char *quote, int exit_status)
// {
// 	int		len;
// 	int		start;
// 	char	*pos;
// 	char	*value;
// 	char	*var;

// 	pos = ft_strchr(quote, '$') + 1;
// 	start = pos - quote;
// 	len = word_len(quote, start);
// 	var = ft_substr(quote, start, len);
// 	if (ft_strncmp(var, "?", 2) == 0)
// 		return (ft_itoa(exit_status));
// 	if (!var)
// 		return (NULL);
// 	value = getenv(var);
// 	if (value)
// 		return (free(var), ft_strdup(value));
// 	return (var);
// }

char	*expand_var(t_list **env_list, char *var, int exit_status)
{
	char	*name_var;
	char	*value;

	if (ft_strncmp(var, "$?", 3) == 0)
		return (ft_itoa(exit_status));
	name_var = var + 1;
	value = ft_getenv(env_list, name_var);
	if (value)
		return (ft_strdup(value));
	return (ft_strdup(var));
}

int	chr_repeat(char *s, int c)
{
	int	res;

	res = 0;
	while (*s)
	{
		if (*s == c)
			res++;
		s++;
	}
	return (res);
}

char	*expanded_str(t_list **env_list, char *str, int exit_status)
{
	char	*start_str;
	char	*partial_str;
	char	*final_str;
	int	start_index;
	// char	*end_str;
	char	*value;
	// int	exp_nbr;
	// int	i;

	// i = 0;
	// exp_nbr = chr_repeat(str, '$');
	// while (str[i])
	// {
		
	// }
	start_index = ft_strchr(str, '$') - str;
	start_str = ft_substr(str, 0, start_index);
	value = expand_var(env_list, ft_strchr(str, '$'), exit_status);
	partial_str = ft_strjoin(start_str, value);
	// end_str = ft_strchr(quote, '$') + word_len(quote, start_quote);
	final_str = ft_strjoin(partial_str, (ft_strchr(str, '$') + word_len(str, start_index)));
	// printf("%s\n", final_str);
	free(value);
	free(start_str);
	free(partial_str);
	return (final_str);
}

char	get_kind_of_quote(char *str)
{
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
			return(*str);
		str++;
	}
	return (0);	
}

char	**expand_env_var(t_list **env_list, char **token, int exit_status)
{
	int		i;
	char	**expanded_token;
	char	quote;

	i = 0;
	expanded_token = malloc(sizeof(char *) * (array_size((void **)token) + 1));
	if (!expanded_token)
		return (NULL);
	while (token[i])
	{
		if (ft_strchr(token[i], '$'))
		{
			quote = get_kind_of_quote(token[i]);
			printf("%c\n", quote);
			if (quote == '\'')
			{
				printf("KK\n");
				expanded_token[i] = ft_strdup(token[i]);
				printf("%s\n", expanded_token[i]);
			}
			else
				expanded_token[i] = expanded_str(env_list, token[i], exit_status);
			// else if (*token[i] == '\"')
			// 	expanded_token[i] = expanded_quote(token[i], exit_status);
			// else
			// 	expanded_token[i] = expand_var(token[i], exit_status);
		}
		else
			expanded_token[i] = ft_strdup(token[i]);
		i++;
	}
	expanded_token[i] = NULL;
	return (ft_free((void **)token, -1), expanded_token);
}
