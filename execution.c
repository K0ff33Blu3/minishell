/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emondo <emondo@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:51:52 by miricci           #+#    #+#             */
/*   Updated: 2025/06/15 21:30:04 by emondo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(t_cmdline *data)
{
	printf("DEBUG: comando ricevuto: '%s'\n", data->cmd);

	if (ft_strncmp(data->cmd, "echo", 5) == 0)
	{
		echo(data);
		return (1);
	}
	else if (ft_strncmp(data->cmd, "exit", 5) == 0)
	{
		exit_cmd(data); // chiama exit(), quindi il return non serve in teoria
		return (1);
	}
	else if (ft_strncmp(data->cmd, "cd", 3) == 0)
	{
		ft_cd(data);
		return (1);
	}
	return (0); // non era un built-in
}

void one_cmd(t_cmdline *data, int fd, char **envp)
{
    pid_t pid;
    (void)fd;

    pid = fork();
    if (pid < 0)
        perror("fork");
    if (pid == 0)
    {
        reset_signals_default();
	data_parsing(data->all_cmd_lines[0], data);
        if (data->cmd && execute_builtin(data))
            exit(EXIT_SUCCESS);
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