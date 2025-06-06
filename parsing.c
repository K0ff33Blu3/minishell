/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:03:04 by miricci           #+#    #+#             */
/*   Updated: 2025/06/03 11:43:04 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**remove_quotes(char **str)
{
	int	i;
	char	quote;
	char	**no_quotes;

	no_quotes = malloc(sizeof(char *) * (array_size((void **)str) + 1));
	if (!no_quotes)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (*str[i] == '\'' || *str[i] == '\"')
		{
			quote = *str[i];
			no_quotes[i] = ft_strtrim(str[i], &quote);
		}
		else
			no_quotes[i] = ft_strdup(str[i]);
		i++;
	}
	no_quotes[i] = NULL;
	return (ft_free((void **)str, -1), no_quotes);
}

char	**get_data_token(char *str)
{
	char	**partial_token;
	char	**exp_token;
	char	**re_token;
	char	**no_quotes_token;

	partial_token = tokenize(str);
	if (!partial_token)
		return (NULL);
	exp_token = expand_env_var(partial_token);
	if (!exp_token)
		return (NULL);
	re_token = re_tokenize(exp_token, array_size((void **)exp_token));
	ft_free((void **)exp_token, -1);
	no_quotes_token = remove_quotes(re_token);
	if (!no_quotes_token)
		return (NULL);
	return (no_quotes_token);
}

t_cmdline	*data_init(void)
{
	t_cmdline	*data;
	
	data = (t_cmdline *)malloc(sizeof(t_cmdline));
	ft_memset(data, 0, sizeof(*data));
	if (!data)
		return (NULL);
	return (data);
}

void	data_parsing(char *cmd_str, t_cmdline *data)
{
	data->token = get_data_token(cmd_str);
	handle_input_redir(data);
	handle_output_redir(data);
	// print_cmd_struct(*data, fd);
}

void	close_pipe(t_cmdline *cmd)
{
	close(cmd->pipe[0]);
	close(cmd->pipe[1]);
}

void	ft_fork(char *cmd_line, int fd)
{
	pid_t	pid;
	t_cmdline	*data;

	data = data_init();
	if (pipe(data->pipe) == -1)
		perror("pipe");
	pid = fork();
	if (pid < 0)
		perror("fork");
	if (pid == 0)
	{
		data_parsing(cmd_line, data);
		print_cmd_struct(*data, fd);
		dup2(data->pipe[1], STDOUT_FILENO);
		close_pipe(data);
		// if (!(data->out_fd < 0))
		// 	close(data->out_fd);
		// exec_command(*pipex, envp);
	}
	else
	{
		close(data->pipe[1]);
		dup2(data->pipe[0], STDIN_FILENO);
		close(data->pipe[0]);
	}
}

void	pipe_parsing(char *cmd_line)
{
	// t_list		**head;
	// t_list		*node;
	char	**splitted_cmd_line;
	int	i;
	int fd = open("output_check", O_RDWR);
	if (fd < 0)
		return ;
	i = 0;
	// head = malloc(sizeof(t_list));
	// if (!head)
	// 	return (NULL);
	// *head = NULL;
	splitted_cmd_line = ft_split(cmd_line, '|');
	if (!splitted_cmd_line)
		return ;
	while (splitted_cmd_line[i])
	{
		ft_fork(splitted_cmd_line[i], fd);
		ft_putnbr_fd(i, fd);
		// node = ft_lstnew((void *)data);
		// if (!node)
		// 	return (NULL);
		// ft_lstadd_back(head, node);
		i++;
	}
	ft_free((void **)splitted_cmd_line, -1);
	// return (head);
}
