/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:52:14 by miricci           #+#    #+#             */
/*   Updated: 2025/06/13 12:37:54 by miricci          ###   ########.fr       */
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

void	create_pipe(char *cmd_line, int i, int size, char **envp, int pip[2][2])
{
	pid_t	pid;
	t_cmdline	*data;
	// int	status;
	// (void)fd;

	data = data_init();
	pid = fork();
	if (pid < 0)
		ft_error("fork");
	if (pid == 0)
	{
		data_parsing(cmd_line, data);
		// print_cmd_struct(*data, 1);
		if (i > 0 && !data->has_infile)
			dup2(pip[(i + 1) % 2][0], STDIN_FILENO);
		if (i < size - 1 && !data->has_outfile)
			dup2(pip[i % 2][1], STDOUT_FILENO);
		close(pip[(i + 1) % 2][0]);
		close(pip[i % 2][1]);
		exec_command(data, envp);
	}
	else
	{
		// wait(NULL);		//da togliere
		if (i < size - 1)
		{
			close(pip[(i + 1) % 2][0]);
			close(pip[(i + 1) % 2][1]);
		}
	}
}

void	piping(char **cmd_line, int size, char **envp)
{
	int	pip[2][2];
	int	i;

	i = -1;
	while (++i < size)
	{
		if (i < size -1 && pipe(pip[i % 2]) == -1)
			ft_error("pipe");
		create_pipe(cmd_line[i], i, size, envp, pip);
	}
	// i = -1;
// 	while (++i < size)
// 	{
// 		close(pip[i][0]);
// 		close(pip[i][1]);
// 	}
}
