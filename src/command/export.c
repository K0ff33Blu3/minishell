/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:36:15 by miricci           #+#    #+#             */
/*   Updated: 2025/11/25 17:25:33 by miricci          ###   ########.fr       */
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

void	export_error(t_env *env_node, char *str)
{
	ft_putstr_fd("export: \"", STDERR_FILENO);	
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd("\": not a valid identifier", STDERR_FILENO);
	free_env(env_node);
}

static int	export_one(t_list **env_list, char *str)
{
	t_env	*new;
	
	// (void)cmd_list;
	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (EXIT_FAILURE);
	new = mk_env2(find_env_name(str), find_env_value(str));
	printf("%s\n%s\n", new->name, new->value);
	if (!check_name(new->name))
		return (export_error(new, str), EXIT_FAILURE);
	if(update_env(env_list, new))
		ft_lstadd_back(env_list, ft_lstnew(new));
	return (EXIT_SUCCESS);
}

int	export_no_args(t_list **cmd_list, t_cmd *cmd, t_list **env_list, int *status)
{
	t_list	*node;
	t_env	*env;
	int	pid;
	
	pid = fork();
	if (pid < 0)
		return (EXIT_FAILURE);
	if (pid == 0)
	{	
		redirect(cmd_list, env_list, cmd);
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
	return (*status >> 8);
}

int	export(t_list **cmd_list, t_list **env_list, t_cmd *data)
{
	int	i;
	int	status;

	status = 0;
	i = 0;
	if (array_size((void **)data->cmd_args) == 1)
		return (export_no_args(cmd_list, data, env_list, &status));	
	while (data->cmd_args[++i])
		status = export_one(env_list, data->cmd_args[i]);
	return (status);
}
