/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:51:52 by miricci           #+#    #+#             */
/*   Updated: 2025/11/26 13:55:24 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_simple_builtin(t_list **cmd_lst, t_cmd *data, t_list **env_list)
{
	if (ft_strncmp(data->cmd, "echo", 5) == 0)
		echo(data);
	else if (ft_strncmp(data->cmd, "env", 4) == 0)
		env(env_list);
	else if (ft_strncmp(data->cmd, "pwd", 4) == 0)
		pwd();
	ft_lstclear(cmd_lst, clean_data);
	ft_lstclear(env_list, free_env);
	exit(EXIT_SUCCESS);
}

int	exec_status_builtin(t_list **cmd, t_cmd *data, t_list **env, int *status)
{
	if (!data->cmd)
		return (0);
	if (ft_strncmp(data->cmd, "exit", 5) == 0)
	{
		exit_cmd(env, cmd, data);
		return (1);
	}
	else if (ft_strncmp(data->cmd, "cd", 3) == 0)
	{
		*status = ft_cd(env, data);
		return (1);
	}
	else if (ft_strncmp(data->cmd, "unset", 6) == 0)
	{
		*status = unset(env, data->cmd_args);
		return (1);
	}
	else if (ft_strncmp(data->cmd, "export", 7) == 0)
	{
		*status = export(cmd, env, data);
		return (1);
	}
	return (0);
}

void	exec_command(t_list **cmd_list, t_cmd *data, t_list **env_list)
{
	char	**env;
	int		path_ctrl;

	if (!data->cmd)
	{
		ft_lstclear(env_list, free_env);
		ft_lstclear(cmd_list, clean_data);
		exit(EXIT_SUCCESS);
	}
	env = envlst_to_envp(env_list);
	path_ctrl = check_cmd_path(data->cmd_path);
	if (path_ctrl == 0)
	{
		if (execve(data->cmd_path, data->cmd_args, env) < 0)
		{
			ft_free((void **)env, -1);
			ft_error(env_list, cmd_list, "execve", EXIT_FAILURE);
		}
	}
	else
	{
		ft_free((void **)env, -1);
		ft_error(env_list, cmd_list, data->cmd, path_ctrl);
	}
}
