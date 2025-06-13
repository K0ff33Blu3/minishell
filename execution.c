/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:51:52 by miricci           #+#    #+#             */
/*   Updated: 2025/06/12 16:40:12 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	one_cmd(char *cmd_line, int fd, char **envp)
{
	pid_t	pid;
	t_cmdline	*data;
	// int	status;
	(void)fd;

	data = data_init();
	pid = fork();
	if (pid < 0)
		perror("fork");
	if (pid == 0)
	{
		data_parsing(cmd_line, data);
		// print_cmd_struct(*data, fd);
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