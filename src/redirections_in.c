/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_in.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 17:40:26 by miricci           #+#    #+#             */
/*   Updated: 2025/12/01 16:04:03 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_line_heredoc_loop(t_cmd *cmd, char *limiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (g_last_sig == SIGINT)
		{
			close_pipe(cmd->tmp_pipe);
			exit(130);
		}
		if (!line && g_last_sig != SIGINT)
		{
			printf("warning: %s requested\n", limiter);
			close_pipe(cmd->tmp_pipe);
			exit(EXIT_SUCCESS);
		}
		if (!ft_strncmp(line, limiter, ft_strlen(limiter) + 1))
		{
			free(line);
			close_pipe(cmd->tmp_pipe);
			exit(EXIT_SUCCESS);
		}
		ft_putendl_fd(line, cmd->tmp_pipe[1]);
		free(line);
	}
}

int	handle_heredoc(t_cmd *cmd, char *limiter)
{
	pid_t	pid;
	int		status;

	if (pipe(cmd->tmp_pipe) == -1)
		perror("pipe");
	pid = fork();
	if (pid == 0)
	{
		here_doc_signals();
		get_line_heredoc_loop(cmd, limiter);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		close(cmd->tmp_pipe[1]);
		waitpid(pid, &status, 0);
		waiting_signals();
		if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
			return (clean_sigint(cmd), -1);
	}
	return (cmd->tmp_pipe[0]);
}

int	open_infile(t_cmd *cmd, int i, char **infile, int *last_fd)
{
	int	flag;

	flag = 0;
	free(*infile);
	*infile = ft_strdup(cmd->token[i + 1]);
	if (*last_fd > 0)
		close(*last_fd);
	if (!ft_strncmp(cmd->token[i], "<", 2))
	{
		*last_fd = open(*infile, O_RDONLY);
		flag = 1;
		if (*last_fd == -1)
		{
			*last_fd = open("/dev/null", O_RDONLY);
			return (-1);
		}
	}
	else if (!ft_strncmp(cmd->token[i], "<<", 3))
	{
		*last_fd = handle_heredoc(cmd, *infile);
		flag = 2;
	}
	return (flag);
}

int	handle_input_redir(t_cmd *cmd)
{
	char	*infile;
	int		i;
	int		flag;
	int		last_fd;

	i = -1;
	flag = 0;
	last_fd = 0;
	infile = NULL;
	while (cmd->token[++i])
	{
		if ((!ft_strncmp(cmd->token[i], "<", 2)
				|| !ft_strncmp(cmd->token[i], "<<", 3))
			&& cmd->token[i + 1])
			flag = open_infile(cmd, i, &infile, &last_fd);
	}
	if (flag != 2)
		cmd->infile = ft_strdup(infile);
	else
		cmd->infile = NULL;
	cmd->in_fd = last_fd;
	free(infile);
	return (flag);
}
