/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emondo <emondo@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:52:14 by miricci           #+#    #+#             */
/*   Updated: 2025/10/16 15:15:44 by emondo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static void	child_setup_and_exec(t_cmdline *data, int i, int size, t_list **env_list, int exit_status)
{
	reset_signals_default();
	data_parsing(env_list, data->all_cmd_lines[i], data, exit_status);
	if (i > 0 && !data->has_infile)
		dup2(data->pip[(i + 1) % 2][0], STDIN_FILENO);
	if (i < size - 1 && !data->has_outfile)
		dup2(data->pip[i % 2][1], STDOUT_FILENO);
	if (i > 0)
		close(data->pip[(i + 1) % 2][0]);
	if (i < size - 1)
		close(data->pip[i % 2][1]);
	if (exec_status_changing_builtin(data, env_list))
	{
		free_cmdline(data);
		exit(EXIT_SUCCESS);
	}
	exec_simple_builtin(data, env_list);
	exec_command(data, env_list);
	exit(127);
}

pid_t	create_pipe(t_cmdline *data, int i, int size, t_list **env_list, int exit_status)
{
    pid_t pid = fork();
    if (pid < 0)
        ft_error("fork");
    if (pid == 0) 
    	child_setup_and_exec(data, i, size,  env_list, exit_status);
    else
    {
        if (i > 0)
            close(data->pip[(i + 1) % 2][0]);
        if (i < size - 1)
            close(data->pip[i % 2][1]);
    }
    return (pid);
}

int	piping(t_cmdline *data, int *exit_status, int size, t_list **env_list)
{
	int	i;
	int	status;
	int	pid;

	setup_shell_signals_father();
	i = -1;
	while (++i < size)
	{
		if (i < size - 1 && pipe(data->pip[i % 2]) == -1)
			ft_error("pipe");
		pid = create_pipe(data, i, size, env_list, *exit_status);
	}
	waitpid(pid, &status, 0);
	apply_status_and_restore_prompt(status, exit_status);
	return (*exit_status);
}
