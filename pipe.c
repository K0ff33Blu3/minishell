/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:52:14 by miricci           #+#    #+#             */
/*   Updated: 2025/06/14 12:59:16 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipe(int pip[2][2])
{
	close(pip[0][0]);
	close(pip[0][1]);
	close(pip[1][0]);
	close(pip[1][1]);
}

void	create_pipe(t_cmdline *data, int i, int size, char **envp)
{
	pid_t	pid;
	// int	status;
	// (void)fd;

	pid = fork();
	if (pid < 0)
		ft_error("fork");
	if (pid == 0)
	{
		printf("cmd_str: %s\n", data->all_cmd_lines[i]);
		data_parsing(data->all_cmd_lines[i], data);
		print_cmd_struct(*data, 1);
		if (i > 0 && !data->has_infile)
			dup2(data->pip[(i + 1) % 2][0], STDIN_FILENO);
		if (i < size - 1 && !data->has_outfile)
			dup2(data->pip[i % 2][1], STDOUT_FILENO);
		close(data->pip[(i + 1) % 2][0]);
		close(data->pip[i % 2][1]);
		exec_command(data, envp);
	}
	else
	{
		wait(NULL);		//da togliere
		if (i < size - 1)
		{
		// 	close(data->pip[(i) % 2][0]);
		// 	close(data->pip[(i) % 2][1]);
		}
	}
}

void	piping(t_cmdline *data, int size, char **envp)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		if (i < size - 1 && pipe(data->pip[i]) == -1)
			ft_error("pipe");
		create_pipe(data, i, size, envp);
	}
	// i = -1;
// 	while (++i < size)
// 	{
// 		close(pip[i][0]);
// 		close(pip[i][1]);
// 	}
}
