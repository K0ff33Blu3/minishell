/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:52:14 by miricci           #+#    #+#             */
/*   Updated: 2025/06/12 16:39:47 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_pipe(char *cmd_line, int i, int size, char **envp, int (*pip)[2])
{
	pid_t	pid;
	t_cmdline	*data;
	// int	status;
	// (void)fd;

	data = data_init();
	if (pipe(pip[i]) == -1)
		perror("pipe");
	pid = fork();
	if (pid < 0)
		perror("fork");
	if (pid == 0)
	{
		data_parsing(cmd_line, data);
		// print_cmd_struct(*data, fd);
		if (i > 0 && !data->has_infile)
			dup2(pip[i - 1][0], STDIN_FILENO);
		if (i < size - 1 && !data->has_outfile)
			dup2(pip[i][1], STDOUT_FILENO);
		close(pip[i - 1][0]);
		close(pip[i - 1][1]);
		exec_command(data, envp);
	}
	else
	{
		// wait(NULL);		//da togliere
		close(pip[i - 1][0]);
		close(pip[i - 1][1]);
	}
}

void	piping(char **cmd_line, int size, char **envp)
{
	int	(*pip)[2];
	int	i;

	pip = malloc(sizeof(int[2]) * (size - 1));
	if (!pip)
		perror("malloc");
	i = -1;
	while (++i < size - 1)
		create_pipe(cmd_line[i], i, size, envp, pip);
	free(pip);
}