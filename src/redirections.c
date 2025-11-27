/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 08:22:00 by miricci           #+#    #+#             */
/*   Updated: 2025/11/27 14:38:41 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir(char **token, int i)
{
	if (token[i])
	{
		if (!ft_strncmp(token[i], "<", 2) || !ft_strncmp(token[i], "<<", 3)
			|| !ft_strncmp(token[i], ">", 2) || !ft_strncmp(token[i], ">>", 3))
		{
			if (token[i + 1] && !is_metachar(token[i + 1]))
				return (EXIT_SUCCESS);
			else
				return (SYNT_ERR);
		}
		else
			return (EXIT_FAILURE);
	}
	return (EXIT_FAILURE);
}

int	check_file_path(char *path, int perm_code)
{
	struct stat	st;

	if (!stat(path, &st))
	{
		if (!access(path, perm_code))
		{
			if (S_ISDIR(st.st_mode))
				return (IS_DIR);
			else
				return (EXIT_SUCCESS);
		}
		return (NO_PERM);
	}
	return (EXIT_FAILURE);
}

void	ft_dup2(int dst_fd, int src_fd)
{
	dup2(dst_fd, src_fd);
	close(dst_fd);
}

void	redirect(t_list **cmd, t_list **env, t_cmd *data)
{
	int	check;

	if (data->has_outfile && data->outfile)
	{
		check = check_file_path(data->outfile, W_OK);
		if (!check)
			ft_dup2(data->out_fd, STDOUT_FILENO);
		else
			ft_redir_err(env, cmd, data->outfile, check);
	}
	if (data->has_infile && data->infile)
	{
		check = check_file_path(data->infile, R_OK);
		if (!check)
			ft_dup2(data->in_fd, STDIN_FILENO);
		else
			ft_redir_err(env, cmd, data->infile, check);
	}
	else if (data->has_infile == 2)
		ft_dup2(data->tmp_pipe[0], STDIN_FILENO);
}

int	handle_heredoc(t_cmd *cmd, char *limiter)
{
	char	*line;
	pid_t	pid;
	int	status;
	
	if (pipe(cmd->tmp_pipe) == -1)
		perror("pipe");
	pid = fork();
	if (pid == 0)
	{
		while (1)
		{
			line = readline("> ");
			if (!line)
			{
				printf("warning: %s requested\n", limiter);
				break ;
			}
			if (!ft_strncmp(line, limiter, ft_strlen(limiter) + 1))
			{
				free(line);
				break ;
			}
			ft_putendl_fd(line, cmd->tmp_pipe[1]);
			free(line);
		}
	}
	else
	{
		close(cmd->tmp_pipe[1]);
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		{
			g_last_sig = SIGINT;
			close(cmd->tmp_pipe[0]);
			return (-1);
		}
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
