/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:51:52 by miricci           #+#    #+#             */
/*   Updated: 2025/06/14 13:01:16 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(t_cmdline *data)
{
	if (ft_strncmp(data->cmd, "echo", 5) == 0)
		echo_builtin(data);
	return (0);
}

void	one_cmd(t_cmdline *data, int fd, char **envp)
{
	pid_t	pid;
	// int	status;
	(void)fd;

	pid = fork();
	if (pid < 0)
		perror("fork");
	if (pid == 0)
	{
		data_parsing(data->all_cmd_lines[0], data);
		print_cmd_struct(*data, 1);
		exec_command(data, envp);
	}
}

void	exec_command(t_cmdline *data, char **envp)
{
	if (access(data->cmd_path, X_OK) != -1)
	{
		if (execve(data->cmd_path, data->cmd_args, envp) < 0)
		{
			ft_free((void **)data->cmd_args, -1);
			free(data->cmd);
			free(data->cmd_path);
			ft_error("execve");
		}
	}
}