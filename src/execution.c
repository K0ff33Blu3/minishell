/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:51:52 by miricci           #+#    #+#             */
/*   Updated: 2025/11/13 13:30:53 by miricci          ###   ########.fr       */
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
	close_pipe(data->pip);
	ft_lstclear(cmd_lst, clean_data);
	ft_lstclear(env_list, free_env);
	exit(EXIT_SUCCESS);
}

int	exec_status_changing_builtin(t_cmd *data, t_list **env_list, int *exit_status)
{
	if (ft_strncmp(data->cmd, "exit", 5) == 0)
	{
		exit_cmd(data);
		return (1);
	}
	else if (ft_strncmp(data->cmd, "cd", 3) == 0)
	{
		*exit_status = ft_cd(env_list, data);
		return (1);
	}
	else if (ft_strncmp(data->cmd, "unset", 6) == 0)
	{
		*exit_status = unset(env_list, data->cmd_args);
		return (1);
	}
	else if (ft_strncmp(data->cmd, "export", 7) == 0)
	{
		*exit_status = export(env_list, data);
		return (1);
	}
	return (0);
}

void	exec_command(t_cmd *data, t_list **env_list)
{
	char	**env;

	env = envlst_to_envp(env_list);
	if (!data->cmd_path)
		ft_error("cmd_not_found");
	if (access(data->cmd_path, X_OK) != -1)
	{
		if (execve(data->cmd_path, data->cmd_args, env) < 0)
		{
			ft_free((void **)data->cmd_args, -1);
			free(data->cmd);
			free(data->cmd_path);
			ft_error("execve");
		}
	}
}
