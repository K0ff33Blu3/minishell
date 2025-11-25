/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 11:40:06 by miricci           #+#    #+#             */
/*   Updated: 2025/11/24 14:27:11 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_var(t_list **env_list, char *var, int exit_status)
{
	char	*value;

	if (ft_strncmp(var, "?", 1) == 0)
		return (ft_itoa(exit_status));
	value = ft_getenv(env_list, var);
	if (value)
		return (value);
	return (NULL);
}

int	find_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '$')
	{
		if (str[i] == '\'')
			i = skip_quote(str, i);
		else
			i++;
	}
	return (i);
}

char	*expand_str(t_list **env_list, char *str, int exit_status, int *i)
{
	char	*fix;
	char	*var;
	char	*part_str;
	char	*result;
	char	*exp_var;

	fix = ft_substr(str, 0, *i);
	var = name_var(str + *i + 1);
	exp_var =  expand_var(env_list, var, exit_status);
	part_str = ft_strjoin(fix, exp_var);
	result = ft_strjoin(part_str, str + *i + 1 + ft_strlen(var));
	*i += ft_strlen(var) + 1;
	free(var);
	free(exp_var);
	free(part_str);
	free(fix);
	return (result);
}

char	*expand_str_recursive(t_list **env_list, char *in_str, int exit_status)
{
	char	*result;
	char	*tmp;
	int	i;
	
	i = find_dollar(in_str);
	if (in_str[i] == '$')
		result = expand_str(env_list, in_str, exit_status, &i);
	else
		result = ft_strdup(in_str);
	if (in_str[i])
	{
		tmp = expand_str_recursive(env_list, result, exit_status);
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
	if (str[name_len] == '?')
		return(ft_strdup("?"));
	while (ft_isalnum(str[name_len]) || str[name_len] == '_')
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

	i = 0;
	expanded_token = malloc(sizeof(char *) * (array_size((void **)token) + 1));
	if (!expanded_token)
		return (NULL);
	while (token[i])
	{
		expanded_token[i] = expand_str_recursive(env_list, token[i], exit_status);
		i++;
	}
	expanded_token[i] = NULL;
	return (ft_free((void **)token, -1), expanded_token);
}
