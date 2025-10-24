/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:36:15 by miricci           #+#    #+#             */
/*   Updated: 2025/10/24 19:51:45 by miricci          ###   ########.fr       */
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
		if (!ft_isalnum(name[i]) && name[i] != '_')
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

static int	export_one(t_list **env_list, char *str)
{
	t_env	*new;
	t_list	*node;
	t_env	*env;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		ft_error("malloc");
	new = mk_env(str);
	if (!check_name(new->name))
	{
		ft_putstr_fd("errore nome variabile\n", 2);	//gestire errore
		return (free_env(new), 1);
	}
	node = *env_list;
	while (node)
	{
		env = (t_env *)node->content;
		if (!ft_strncmp(new->name, env->name, ft_strlen(new->name) + 1))
		{
			free(env->value);
			env->value = ft_strdup(new->value);
			free(new);
			return (0);
		}
		node = node->next;
	}
	ft_lstadd_back(env_list, ft_lstnew(new));
	return (0);
}

int	export_no_args(t_cmd *cmd, t_list **env_list, int *status)
{
	t_list	*node;
	t_env	*env;
	int	pid;
	
	pid = fork();
	if (pid < 0)
		ft_error("fork");
	if (pid == 0)
	{	
		redirect(cmd);
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
		exit(EXIT_SUCCESS);
	}
	if (pid > 0)
		waitpid(pid, status, 0);
	return (*status);
}

int	export(t_list **env_list, t_cmd *data)
{
	int	i;
	int	status;

	status = 0;
	i = 0;
	if (array_size((void **)data->cmd_args) == 1)
		return (export_no_args(data, env_list, &status));	
	while (data->cmd_args[++i])
		status = export_one(env_list, data->cmd_args[i]);
	return (status);
}
