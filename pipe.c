/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:52:14 by miricci           #+#    #+#             */
/*   Updated: 2025/06/16 14:39:31 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void create_pipe(t_cmdline *data, int i, int size, char **envp)
{
    pid_t pid = fork();
    if (pid < 0)
        ft_error("fork");
    if (pid == 0) 
    {
        reset_signals_default();
        data_parsing(data->all_cmd_lines[i], data);
        if (i > 0 && !data->has_infile)  
            dup2(data->pip[(i + 1) % 2][0], STDIN_FILENO);
        if (i < size - 1 && !data->has_outfile)
            dup2(data->pip[i % 2][1],   STDOUT_FILENO);
        if (i > 0)
            close(data->pip[(i + 1) % 2][0]);
        if (i < size - 1)
            close(data->pip[i % 2][1]);
	if (exec_status_changing_builtin(data))
	{
		free_cmdline(data);
		exit(EXIT_SUCCESS);
	}
        exec_simple_builtin(data, envp);
        exec_command(data, envp);
    }
    else
    {
        if (i > 0)
            close(data->pip[(i + 1) % 2][0]);
        if (i < size - 1)
            close(data->pip[i % 2][1]);
    }
}

void	piping(t_cmdline *data, int size, char **envp)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		if (i < size - 1 && pipe(data->pip[i % 2]) == -1)
			ft_error("pipe");
		create_pipe(data, i, size, envp);
	}
}
