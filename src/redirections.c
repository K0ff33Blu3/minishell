/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emondo <emondo@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 08:22:00 by miricci           #+#    #+#             */
/*   Updated: 2025/11/09 15:07:24 by emondo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect(t_cmd *data)
{
	if (data->outfile)
	{
		if (access(data->outfile, W_OK) != -1)
		{
			dup2(data->out_fd, STDOUT_FILENO);
			close(data->out_fd);
		}
		else
			exit(EXIT_FAILURE);
	}
	if (data->infile)
	{
		if (access(data->infile, R_OK) != -1)
		{
			dup2(data->in_fd, STDIN_FILENO);
			close(data->in_fd);
		}
		else
			exit(EXIT_FAILURE);
	}
	if (data->limiter)
	{
		dup2(data->tmp_pipe[0], STDIN_FILENO);
		close(data->tmp_pipe[0]);
	}
}

static void	pop_input(t_cmd *cmd, int type, char *infile, char *limiter)
{
	if (type == 1)
	{
		cmd->infile = ft_strdup(infile);
		cmd->limiter = NULL;	
	}
	else if (type == 2)
	{
		cmd->infile = NULL;	
		cmd->limiter = ft_strdup(limiter);
	}
	else if (type == 0)
	{
		cmd->infile = NULL;
		cmd->limiter = NULL;	
	}
}

int	get_type_of_input(t_cmd *cmd)
{
	int	type;
	int	i;
	char	*infile;
	char	*limiter;

	type = 0;
	i = -1;
	while (cmd->token[++i])
	{
		if(!ft_strncmp(cmd->token[i], "<", 2) && cmd->token[i + 1])
		{
			infile = cmd->token[i + 1];
			type = 1;
		}
		if(!ft_strncmp(cmd->token[i], "<<", 3) && cmd->token[i + 1])
		{
			limiter = cmd->token[i + 1];
			type = 2;
		}
	}
	pop_input(cmd, type, infile, limiter);
	return (type);
}

void	open_infile(t_cmd *cmd)
{
	cmd->in_fd = open(cmd->infile, O_RDONLY);
	if (cmd->in_fd == -1)
	{
		cmd->in_fd = open("/dev/null", O_RDONLY);
		perror(cmd->infile);
	}
}

void	handle_heredoc(t_cmd *cmd)
{
	char	*line;
	
	if (pipe(cmd->tmp_pipe) == -1)
		perror("pipe");
	while (1)
	{
		line = readline("> ");
		if (!ft_strncmp(line, cmd->limiter, ft_strlen(cmd->limiter) + 1))
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, cmd->tmp_pipe[1]);
		free(line);
	}
	close(cmd->tmp_pipe[1]);
}

int	handle_input_redir(t_cmd *cmd)
{
	int	type_of_redir;

	type_of_redir = get_type_of_input(cmd);
	if (type_of_redir == 0)
		cmd->infile = NULL;
	else if (type_of_redir == 1)
		open_infile(cmd);
	else if (type_of_redir == 2)
		handle_heredoc(cmd);
	return (type_of_redir);
}

int	open_outfile(t_cmd *cmd, int i, char **outfile)
{
	int	flag;
	
	flag = 0;
	free(*outfile);
	*outfile = ft_strdup(cmd->token[i + 1]);
	if (!ft_strncmp(cmd->token[i], ">", 2))
	{
		cmd->out_fd = open(*outfile, O_WRONLY | O_CREAT | O_TRUNC, 0664);
		if (cmd->out_fd == -1)
			perror(*outfile);
		flag = 1;
	}
	else if (!ft_strncmp(cmd->token[i], ">>", 3))
	{
		cmd->out_fd = open(*outfile, O_WRONLY | O_CREAT | O_APPEND, 0664);
		flag = 2;	
	}
	return (flag);
}

int	handle_output_redir(t_cmd *cmd)
{
	int	i;
	char	*outfile;
	int	flag;

	i = -1;
	flag = 0;
	outfile = NULL;
	while (cmd->token[++i])
	{
		if((!ft_strncmp(cmd->token[i], ">", 2) || !ft_strncmp(cmd->token[i], ">>", 3)) && cmd->token[i + 1])
			flag = open_outfile(cmd, i, &outfile);
	}
	if (flag)
		cmd->outfile = ft_strdup(outfile);
	else
	{
		cmd->out_fd = STDOUT_FILENO;
		cmd->outfile = NULL;
	}
	free(outfile);
	return (flag);
}
