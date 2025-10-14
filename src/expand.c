/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 11:40:06 by miricci           #+#    #+#             */
/*   Updated: 2025/10/14 17:52:13 by miricci          ###   ########.fr       */
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
	char	*value;

	if (ft_strncmp(var, "?", 3) == 0)
		return (ft_itoa(exit_status));
	printf("var: %s\n", var);
	value = ft_getenv(env_list, var);
	printf("value: %s\n", value);
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

char	*expanded_str(t_list **env_list, char *in_str, int exit_status)
{
	char	*fix;
	char	*exp_var;
	int	i;
	int	var_len;
	char	*var;
	char	*part_str;
	char	*result;
	char	*tmp;

	i = 0;
	while (in_str[i] && in_str[i] != '$')
		i++;
	fix = ft_substr(in_str, 0, i);
	if (in_str[i] == '$')
	{
		var = name_var(in_str + i + 1);
		exp_var =  expand_var(env_list, var, exit_status);
		var_len = ft_strlen(var);
		part_str = ft_strjoin(fix, exp_var);
		result = ft_strjoin(part_str, in_str + i + 1 + var_len);
		free(var);
		free(exp_var);
		free(part_str);
	}
	else
		result = ft_strdup(fix);
	free(fix);
	if (ft_strchr(result, '$'))
	{
		tmp = expanded_str(env_list, result, exit_status);
		free(result);
		result = tmp;
	}
	return (result);
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

char	*name_var(char *str)
{
	char	*name;
	int	name_len;

	name_len = 0;
	while (ft_isalnum(str[name_len]))
		name_len++;
	name = (char *)malloc(sizeof(char) * (name_len + 1));
	if (!name)
		return (NULL);
	ft_strlcpy(name, str, name_len + 1);
	return (name);
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
			if (quote == '\'')
			{
				expanded_token[i] = ft_strdup(token[i]);
			}
			else
			{
				expanded_token[i] = expanded_str(env_list, token[i], exit_status);
			}
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
