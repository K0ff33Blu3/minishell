/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emondo <emondo@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:51:52 by miricci           #+#    #+#             */
/*   Updated: 2025/10/16 14:11:39 by emondo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_simple_builtin(t_cmdline *data, t_list **env_list)
{
	if (data->has_outfile)
	{
		dup2(data->out_fd, STDOUT_FILENO);
		close(data->out_fd);
	}
	if (data->has_infile)
	{
		dup2(data->in_fd, STDIN_FILENO);
		close(data->in_fd);
	}
	if (ft_strncmp(data->cmd, "echo", 5) == 0)
		echo(data);
	else if (ft_strncmp(data->cmd, "env", 4) == 0)
		env(env_list);
	else if (ft_strncmp(data->cmd, "pwd", 4) == 0)
		pwd();
	return (0);
}

int	exec_status_changing_builtin(t_cmdline *data, t_list **env_list)
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
		export(env_list, data->cmd_args);
		return (1);
	}
	return (0);
}

int	one_cmd(t_cmdline *data, int *exit_status, t_list **env_list)
{
	pid_t pid;
	int status;

	data_parsing(env_list, data->all_cmd_lines[0], data, *exit_status);
	if (exec_status_changing_builtin(data, env_list))
		return (0);
	pid = fork();
	if (pid > 0)
	{
		setup_shell_signals_father();
    		waitpid(pid, &status, 0);
		apply_status_and_restore_prompt(status, exit_status);
	}	
	if (pid < 0)
		perror("fork");
	if (pid == 0)
	{
		reset_signals_default();
		exec_simple_builtin(data, env_list);
		exec_command(data, env_list);
	}
	return (0);
}

void	exec_command(t_cmdline *data, t_list **env_list)
{
	char	**env;

	env = lst_to_array(env_list);
	if (data->has_outfile)
	{
		dup2(data->out_fd, STDOUT_FILENO);
		close(data->out_fd);
	}
	if (data->has_infile)
	{
		dup2(data->in_fd, STDIN_FILENO);
		close(data->in_fd);
	}
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
