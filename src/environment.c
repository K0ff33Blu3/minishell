/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 12:08:26 by miricci           #+#    #+#             */
/*   Updated: 2025/11/27 14:00:06 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**envlst_to_envp(t_list **head)
{
	t_list	*node;
	char	*tmp;
	char	**array;
	int		i;

	i = 0;
	node = *head;
	array = (char **)malloc(sizeof(char *) * (ft_lstsize(node) + 1));
	if (!array)
		return (NULL);
	while (node)
	{
		if (((t_env *)node->content)->value)
		{
			tmp = ft_strjoin(((t_env *)node->content)->name, "=");
			array[i] = ft_strjoin(tmp, ((t_env *)node->content)->value);
			free(tmp);
		}
		else
			array[i] = ft_strdup(((t_env *)node->content)->name);
		node = node->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}

t_env	*mk_env(char *name, char *value)
{
	t_env	*env;

	env = (t_env *)malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	if (!value)
	{
		env->name = ft_strdup(name);
		env->value = NULL;
		return (env);
	}
	env->name = ft_strdup(name);
	if (!*value)
	{
		env->value = ft_strdup("");
		return (env);
	}
	env->value = ft_strdup(value);
	free(value);
	free(name);
	return (env);
}

char	*find_env_name(char *str)
{
	int	len;

	len = ft_indchr(str, '=');
	if (len == -1)
		return (ft_strdup(str));
	return (ft_substr(str, 0, len));
}

char	*find_env_value(char *str)
{
	int	len;
	int	name_len;

	name_len = ft_indchr(str, '=');
	if (name_len == -1)
		return (NULL);
	len = ft_strlen(str) - name_len - 1;
	if (len == 0)
		return (ft_strdup(""));
	return (ft_substr(str, name_len + 1, len));
}

int	update_env(t_list **env_list, t_env *new)
{
	t_list	*node;
	t_env	*env;

	node = *env_list;
	while (node)
	{
		env = (t_env *)node->content;
		if (!ft_strncmp(new->name, env->name, ft_strlen(new->name) + 1))
		{
			free(env->value);
			env->value = ft_strdup(new->value);
			free_env(new);
			return (EXIT_SUCCESS);
		}
		node = node->next;
	}
	return (EXIT_FAILURE);
}
