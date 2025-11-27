/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 08:22:00 by miricci           #+#    #+#             */
/*   Updated: 2025/11/26 15:16:11 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_file_path(char *path, int perm_code)
{
	struct stat	st;

	if (!stat(path, &st))
	{
		if (!access(path, perm_code))
		{
			if (S_ISDIR(st.st_mode))
				return(IS_DIR);
			else
				return(EXIT_SUCCESS);
		}
		return (NO_PERM);
	}
	return(EXIT_FAILURE); 
}

void	redirect(t_list **cmd_list, t_list **env_list, t_cmd *data)
{
	if (data->has_outfile && data->outfile)
	{
		if (!check_file_path(data->outfile, W_OK))
		{	
			dup2(data->out_fd, STDOUT_FILENO);
			close(data->out_fd);
		}
		else
			ft_redir_err(env_list, cmd_list, data->outfile, check_file_path(data->outfile, W_OK));
	}
	if (data->has_infile && data->infile)
	{
		if (!check_file_path(data->infile, R_OK))
		{
			dup2(data->in_fd, STDIN_FILENO);
			close(data->in_fd);
		}
		else
			ft_redir_err(env_list, cmd_list, data->infile, check_file_path(data->infile, R_OK));
	}
	else if (data->has_infile == 2)
	{
		dup2(data->tmp_pipe[0], STDIN_FILENO);
		close(data->tmp_pipe[0]);
	}
}

void	open_infile(t_cmd *cmd)
{
	cmd->in_fd = open(cmd->infile, O_RDONLY);
	if (cmd->in_fd == -1)
		cmd->in_fd = open("/dev/null", O_RDONLY);
}

int	handle_heredoc(t_cmd *cmd, char *limiter)
{
	char	*line;
	
	if (pipe(cmd->tmp_pipe) == -1)
		perror("pipe");
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			printf("warning: %s requested\n", limiter);
			break;
		}
		if (!ft_strncmp(line, limiter, ft_strlen(limiter) + 1))
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, cmd->tmp_pipe[1]);
		free(line);
	}
	close(cmd->tmp_pipe[1]);
	return (cmd->tmp_pipe[0]);
}

// int	handle_input_redir(t_cmd *cmd)
// {
// 	int	type_of_redir;

// 	type_of_redir = get_type_of_input(cmd);
// 	if (type_of_redir == 0)
// 		cmd->infile = NULL;
// 	else if (type_of_redir == 1)
// 		cmd->in_fd = open(cmd->infile, O_RDONLY);
// 	else if (type_of_redir == 2)
// 		handle_heredoc(cmd);
// 	return (type_of_redir);
// }

int	open_infile2(t_cmd *cmd, int i, char **infile, int *last_fd)
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

int	handle_input_redir2(t_cmd *cmd)
{
	int	i;
	char	*infile;
	int	flag;
	int	last_fd;

	i = -1;
	flag = 0;
	last_fd = 0;
	infile = NULL;
	while (cmd->token[++i])
	{
		if((!ft_strncmp(cmd->token[i], "<", 2) || !ft_strncmp(cmd->token[i], "<<", 3))
			&& cmd->token[i + 1])
			flag = open_infile2(cmd, i, &infile, &last_fd);
	}
	if (flag != 2)
		cmd->infile = ft_strdup(infile);
	else
		cmd->infile = NULL;
	cmd->in_fd = last_fd;
	free(infile);
	return (flag);
}


