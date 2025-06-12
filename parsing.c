/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:03:04 by miricci           #+#    #+#             */
/*   Updated: 2025/06/12 15:22:27 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**remove_quotes(char **str)
{
	int		i;
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

static int	count_redir(char **token)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (token[i])
	{
		if (*token[i] == '<' || *token[i] == '>')
			count++;
		i++;
	}
	return (count);
}

char	**parse_cmd_args(char **token)
{
	int	i;
	int	j;
	char	**arg;
	int	nbr_redir;
	int	arg_size;

	nbr_redir = count_redir(token);
	arg_size = array_size((void **)token) - (nbr_redir * 2);
	arg = malloc(sizeof(char * ) * (arg_size + 1));
	if (!arg)
		return (NULL);
	i = 0;
	j = 0;
	while (token[i])
	{
		if (*token[i] == '>' || *token[i] == '<')
			i++;
		else if (i > 0 && (*token[i - 1] == '>' || *token[i - 1] == '<'))
			i++;
		else
			arg[j++] = ft_strdup(token[i++]);
	}
	arg[j] = NULL;
	return (arg);
}

void	data_parsing(char *cmd_str, t_cmdline *data)
{
	data->token = get_data_token(cmd_str);
	handle_input_redir(data);
	handle_output_redir(data);
	data->cmd_args = parse_cmd_args(data->token);
	data->cmd = ft_strdup(data->cmd_args[0]);
	data->cmd_path = find_cmd_path(data);
	if (!data->cmd_path)
		cmd_not_found(data);
}

void	ft_fork(char *cmd_line, int fd, int i, int size, char **envp)
{
	pid_t	pid;
	t_cmdline	*data;
	// int	status;
	// (void)fd;

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
		if (i > 0 && !data->infile)
			dup2(data->pipe[0], STDIN_FILENO);
		if (i < size - 1 && !data->outfile)
			dup2(data->pipe[1], STDOUT_FILENO);
		close_pipe(data);
		exec_command(data, envp);
	}
	else
	{
		// wait(NULL);		//da togliere
		close_pipe(data);
	}
}

void	pipe_parsing(char *cmd_line, char **envp)
{
	char	**split_cmd_line;
	int	i;
	int	size;
	int fd = open("output_check", O_RDWR);
	if (fd < 0)
		return ;
	i = 0;
	split_cmd_line = ft_split(cmd_line, '|');
	if (!split_cmd_line)
		return ;
	size = array_size((void **)split_cmd_line);
	while (split_cmd_line[i])
	{
		ft_fork(split_cmd_line[i], 1, i, size, envp);
		// ft_putnbr_fd(i, 1);
		i++;
	}
	while (wait(NULL) != -1)
		;
	ft_free((void **)split_cmd_line, -1);
}
