/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:51:52 by miricci           #+#    #+#             */
/*   Updated: 2025/10/24 19:00:26 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	exec_simple_builtin(t_cmd *data, t_list **env_list)
{
	if (ft_strncmp(data->cmd, "echo", 5) == 0)
		echo(data);
	else if (ft_strncmp(data->cmd, "env", 4) == 0)
		env(env_list);
	else if (ft_strncmp(data->cmd, "pwd", 4) == 0)
		pwd();
	return ;
}

int	exec_status_changing_builtin(t_cmd *data, t_list **env_list)
{
	if (ft_strncmp(data->cmd, "exit", 5) == 0)
	{
		exit_cmd(data);
		return (1);
	}
	else if (ft_strncmp(data->cmd, "cd", 3) == 0)
	{
		ft_cd(env_list, data);
		return (1);
	}
	else if (ft_strncmp(data->cmd, "unset", 6) == 0)
	{
		unset(env_list, data->cmd_args);
		return (1);
	}
	else if (ft_strncmp(data->cmd, "export", 7) == 0)
	{
		export(env_list, data);
		return (1);
	}
	return (0);
}

void	exec_command(t_cmd *data, t_list **env_list)
{
	char	**env;

	env = lst_to_array(env_list);
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
