/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:52:14 by miricci           #+#    #+#             */
/*   Updated: 2025/10/05 20:00:49 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void create_pipe(t_cmdline *data, int i, int size, t_list **env_list)
{
    pid_t pid = fork();
    if (pid < 0)
        ft_error("fork");
    if (pid == 0) 
    {
        reset_signals_default();
        data_parsing(data->all_cmd_lines[i], data);
	// print_cmd_struct(*data, 1);
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
        exec_simple_builtin(data, env_list);
        exec_command(data, env_list);
    }
    else
    {
        if (i > 0)
            close(data->pip[(i + 1) % 2][0]);
        if (i < size - 1)
            close(data->pip[i % 2][1]);
    }
}

void	piping(t_cmdline *data, int size, t_list **env_list)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		if (i < size - 1 && pipe(data->pip[i % 2]) == -1)
			ft_error("pipe");
		create_pipe(data, i, size, env_list);
	}
}
