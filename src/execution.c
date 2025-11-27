/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:51:52 by miricci           #+#    #+#             */
/*   Updated: 2025/11/27 18:45:39 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strncmp(cmd, "echo", 5)
		|| !ft_strncmp(cmd, "env", 4)
		|| !ft_strncmp(cmd, "pwd", 4))
		return (1);
	else if (!ft_strncmp(cmd, "exit", 5)
		|| !ft_strncmp(cmd, "cd", 3)
		|| !ft_strncmp(cmd, "unset", 6)
		|| !ft_strncmp(cmd, "export", 7))
		return (2);
	return (0);
}

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

void	exec_status_builtin(t_list **cmd, t_cmd *data, t_list **env, int *st)
{
	if (!data->cmd)
		return ;
	if (ft_strncmp(data->cmd, "exit", 5) == 0)
		exit_cmd(env, cmd, data);
	else if (ft_strncmp(data->cmd, "cd", 3) == 0)
		*st = ft_cd(env, data);
	else if (ft_strncmp(data->cmd, "unset", 6) == 0)
		*st = unset(env, data->cmd_args);
	else if (ft_strncmp(data->cmd, "export", 7) == 0)
		*st = export(cmd, env, data);
	clean_data(data);
}

int	ft_single_builtin(t_list **cmd, t_list **env, int *status)
{
	t_cmd	*data;

	data = (t_cmd *)(*cmd)->content;
	if (ft_lstsize(*cmd) == 1 && is_builtin(data->cmd) == 2)
	{
		exec_status_builtin(cmd, data, env, status);
		free(*cmd);
		free(cmd);
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
