/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 08:22:00 by miricci           #+#    #+#             */
/*   Updated: 2025/06/03 11:51:12 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmd_struct(t_cmdline cmd, int fd)
{
	int	i;

	i = -1;
	ft_putendl_fd("\nTOKEN", fd);
	while (cmd.token[++i])
	{
		ft_putstr_fd("token[", fd);
		ft_putnbr_fd(i, fd);
		ft_putstr_fd("]: ", fd);
		ft_putendl_fd(cmd.token[i], fd);
	}
	// printf("CMD: %s\n", cmd.cmd);
	// printf("CMD_PATH: %s\n", cmd.cmd_path);
	// i = -1;
	// printf("\nCMD_PATH\n")
	// while (cmd.cmd_path[++i])
	// 	printf("token[%d]: %s\n", i, cmd.cmd_path[i]);
	ft_putstr_fd("IN_FD: ", fd);
	ft_putnbr_fd(cmd.in_fd, fd);
	ft_putstr_fd("\n", fd);
	ft_putstr_fd("OUT_FD: ", fd);
	ft_putnbr_fd(cmd.out_fd, fd);
	ft_putstr_fd("\n", fd);
	ft_putstr_fd("INFILE: ", fd);
	ft_putstr_fd(cmd.infile, fd);
	ft_putstr_fd("\n", fd);
	ft_putstr_fd("OUTFILE: ", fd);
	ft_putstr_fd(cmd.outfile, fd);
	ft_putstr_fd("\n", fd);
}

int	get_type_of_input(t_cmdline *cmd)
{
	int	type;
	int	i;
	char	*infile;
	char	*limiter;

	type = 0;
	i = -1;
	infile = NULL;
	limiter = NULL;
	while (cmd->token[++i])
	{
		if(!ft_strncmp(cmd->token[i], "<", 2) && cmd->token[i + 1])
		{
			// free(infile);
			infile = cmd->token[i + 1];
			type = 1;			
		}
		if(!ft_strncmp(cmd->token[i], "<<", 3) && cmd->token[i + 1])
		{
			free(limiter);
			limiter = ft_strjoin(cmd->token[i], "\n");
			type = 2;
		}
	}
	if (type == 1)
		cmd->infile = ft_strdup(infile);
	if (type == 2)
		cmd->limiter = ft_strdup(limiter);
	return (free(limiter), type);
}

int	handle_input_redir(t_cmdline *cmd)
{
	char	*line;
	int	type_of_redir;

	type_of_redir = 0;
	type_of_redir = get_type_of_input(cmd);
	if (type_of_redir == 1)
	{
		cmd->in_fd = open(cmd->infile, O_RDONLY);
		if (cmd->in_fd == -1)
		{
			cmd->in_fd = open("/dev/null", O_RDONLY);
			perror(cmd->infile);
		}
		dup2(cmd->in_fd, STDIN_FILENO);
		close(cmd->in_fd);
	}
	else if (type_of_redir == 2)
	{
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
			ft_putstr_fd(line, cmd->tmp_pipe[1]);
			free(line);
		}
		dup2(cmd->tmp_pipe[0], STDIN_FILENO);
		close(cmd->tmp_pipe[0]);
		close(cmd->tmp_pipe[1]);
	}
	return (type_of_redir);
}

void	open_outfile(t_cmdline *cmd, int i, int *flag, char **outfile)
{
	free(*outfile);
		*outfile = ft_strdup(cmd->token[i + 1]);
	if (!ft_strncmp(cmd->token[i], ">", 2))
		cmd->out_fd = open(*outfile, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	else if (!ft_strncmp(cmd->token[i], ">>", 3))
		cmd->out_fd = open(*outfile, O_WRONLY | O_CREAT | O_APPEND, 0664);
	*flag = 1;
}

int	handle_output_redir(t_cmdline *cmd)
{
	int	type;
	int	i;
	char	*outfile;
	int	flag;

	flag = 0;
	type = 0;
	i = -1;
	outfile = NULL;
	while (cmd->token[++i])
	{
		if((!ft_strncmp(cmd->token[i], ">", 2) || !ft_strncmp(cmd->token[i], ">>", 3)) && cmd->token[i + 1])
			open_outfile(cmd, i, &flag, &outfile);
	}
	if (flag)
	{
		cmd->outfile = ft_strdup(outfile);
		dup2(cmd->out_fd, STDOUT_FILENO);
		close(cmd->out_fd);
	}
	else
		cmd->out_fd = STDOUT_FILENO;
	return (free(outfile), type);
}

// int	handle_output_redir(t_cmdline *cmd)
// {
// 	int	type_of_redir;

// 	type_of_redir = get_type_of_output(cmd);
// 	if (type_of_redir)
// 	{
// 		if (type_of_redir == 1)
// 		else if (type_of_redir == 2)
			
		
// 	}
// 	else
// 		cmd->out_fd = STDOUT_FILENO;
// 	return(type_of_redir);
// }

// int main(void)
// {
// 	t_cmdline	*result;
// 	char	*str = "cat < in1 < in2 > out1 > out2";
// 	int i = 0;

// 	result = data_parsing(str);
// 	print_cmd_struct(*result);
// 	free(result);
// 	return (0);	
// }
