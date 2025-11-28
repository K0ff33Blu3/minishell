/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 11:40:06 by miricci           #+#    #+#             */
/*   Updated: 2025/11/28 23:37:22 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_var(t_list **env_list, char *var, int exit_status)
{
	char	*value;

	if (ft_strncmp(var, "?", 2) == 0)
		return (ft_itoa(exit_status));
	value = ft_getenv(env_list, var);
	if (value)
		return (value);
	return (ft_strdup(""));
}

char	*expand_backslash(char *str, int *i)
{
	char	*result;
	char	*fix;
	char	*tmp;
	char	*exp;

	exp = (char *)malloc(sizeof(char) * 2);
	if (!exp)
		return (NULL);
	exp[0] = str[*i + 1];
	exp[1] = 0;
	fix = ft_substr(str, 0, *i);
	tmp = ft_strjoin(fix, exp);
	printf("%s\n", exp);
	result = ft_strjoin(tmp, str + ft_strlen(exp));
	*i += 2;
	free(fix);
	free(tmp);
	return (result);
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
	exp_var = expand_var(env_list, var, exit_status);
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
	int		i;

	i = find_dollar(in_str);
	if (in_str[i] == '\\')
		result = expand_backslash(in_str, &i);
	else if (in_str[i] == '$')
		result = expand_str(env_list, in_str, exit_status, &i);
	else
		return (ft_strdup(in_str));
	tmp = expand_str_recursive(env_list, result, exit_status);
	free(result);
	return (tmp);
}

char	*name_var(char *str)
{
	char	*name;
	int		name_len;

	name_len = 0;
	if (str[name_len] == '?')
		return (ft_strdup("?"));
	while (ft_isalnum(str[name_len]) || str[name_len] == '_')
		name_len++;
	name = (char *)malloc(sizeof(char) * (name_len + 1));
	if (!name)
		return (NULL);
	ft_strlcpy(name, str, name_len + 1);
	return (name);
}

char	**expand_env_var(t_list **env_list, char **token, int status)
{
	int		i;
	char	**expanded_token;

	i = 0;
	expanded_token = malloc(sizeof(char *) * (array_size((void **)token) + 1));
	if (!expanded_token)
		return (NULL);
	while (token[i])
	{
		expanded_token[i] = expand_str_recursive(env_list, token[i], status);
		i++;
	}
	expanded_token[i] = NULL;
	return (ft_free((void **)token, -1), expanded_token);
}
