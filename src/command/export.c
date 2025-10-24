/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:36:15 by miricci           #+#    #+#             */
/*   Updated: 2025/10/24 16:17:18 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_name(char	*name)
{
	int	i;

	i = 0;
	if (!ft_isalpha(name[0]))
		return (0);
	while (name[i])
	{
		if (!ft_isalnum(name[i]))
			return (0);
		i++;
	}
	return (1);
}

void	free_env(t_env *env)
{
	if (env)
	{
		if (!env->name)
			free(env->name);
		if (!env->value)
			free(env->value);
		free(env);
	}
}

static void	export_one(t_list **env_list, char *str)
{
	t_env	*new;
	t_list	*node;
	t_env	*env;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return ;
	new = mk_env(str);
	if (!check_name(new->name))
		ft_putstr_fd("errore nome variabile", 2);	//gestire errore
	node = *env_list;
	while (node)
	{
		env = (t_env *)node->content;
		if (!ft_strncmp(new->name, env->name, ft_strlen(new->name) + 1))
		{
			free(env->value);
			env->value = ft_strdup(new->value);
			free(new);
			return ;
		}
		node = node->next;
	}
	ft_lstadd_back(env_list, ft_lstnew(new));
}

void	export_no_args(t_list **env_list)
{
	t_list	*node;
	t_env	*env;
	
	node = *env_list;
	while (node)
	{
		env = (t_env *)node->content;
		if (env->value)
			printf("declare -x %s=\"%s\"\n", env->name, env->value);
		else
			printf("declare -x %s\n", env->name);
		node = node->next;
	}
}

void	export(t_list **env_list, char **str)
{
	int	i;

	i = 0;
	if (array_size((void **)str) == 1)
		return (export_no_args(env_list));	
	while (str[++i])
		export_one(env_list, str[i]);
}
