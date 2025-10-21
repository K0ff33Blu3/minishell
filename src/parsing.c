/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:03:04 by miricci           #+#    #+#             */
/*   Updated: 2025/10/21 17:02:19 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*rm_quotes(char *str)
{
	int	i;
	int	j;
	char	quote;
	char	*no_quote;

	i = 0;
	j = 0;
	no_quote = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!no_quote)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i];
			i++;
			while (str[i] && str[i] != quote)
			{
				no_quote[j] = str[i];
				j++;
				i++;
			}
			if (str[i] == quote)
				i++;
		}
		else
		{
			no_quote[j] = str[i];
			j++;
			i++;
		}
	}
	no_quote[j] = 0;
	return (no_quote);
}

char	**remove_quotes(char **str)
{
	int		i;
	char	**no_quotes;

	no_quotes = malloc(sizeof(char *) * (array_size((void **)str) + 1));
	if (!no_quotes)
		return (NULL);
	i = 0;
	while (str[i])
	{
		no_quotes[i] = rm_quotes(str[i]);
		i++;
	}
	no_quotes[i] = NULL;
	return (ft_free((void **)str, -1), no_quotes);
}

t_cmd	*data_init(void)
{
	t_cmd	*data;

	data = (t_cmd *)malloc(sizeof(t_cmd));
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
	char		**arg;
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

char	**get_cmd_token(char **all_token, int start, int end)
{
	char	**result;
	int	i;
	
	result = (char **)malloc(sizeof(char *) * (end - start + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (start < end)
	{
		result[i] = ft_strdup(all_token[start]);
		start++;
		i++;
	}
	result[i] = NULL;
	return (result);
}

int	find_pipe(char **token, int *start)
{
	int	end;
	
	if (!ft_strncmp(token[*start], "|", 2))
		(*start)++;
	end = *start;
	while (token[end] && ft_strncmp(token[end], "|", 2))
		end++;
	return (end);
}

char	**token_parsing(t_list **env_list, char **token, int *exit_code)
{
	char	**exp_token;
	char	**no_quotes_token;

	exp_token = expand_env_var(env_list, token, *exit_code);
	if (!exp_token)
		return (NULL);
	no_quotes_token = remove_quotes(exp_token);
	if (!no_quotes_token)
		return (NULL);
	return (no_quotes_token);
}

t_cmd	*data_parsing(t_list **env_list, char **part_token, int *exit_status)
{
	t_cmd	*data;
	
	data = data_init();
	data->token = token_parsing(env_list, part_token, exit_status);
	data->has_infile = handle_input_redir(data);
	data->has_outfile = handle_output_redir(data);
	data->cmd_args = parse_cmd_args(data->token);
	if (!data->cmd_args || !data->cmd_args[0])
	{
		data->cmd = NULL;
		data->cmd_path = NULL;
		return (NULL);
	}
	data->cmd = ft_strdup(data->cmd_args[0]);
	if (is_builtin(data->cmd))
		data->cmd_path = NULL;
	else
	{
		data->cmd_path = find_cmd_path(data);
		if (!data->cmd_path)
			cmd_not_found(data);
	}
	return (data);			
}

char	**array_cpy(char **src)
{
	char	**dst;
	int	i;

	dst = (char **)malloc(sizeof(char *) * (array_size((void **)src) + 1));
	if (!dst)
		return (NULL);
	i = -1;
	while (src[++i])
	{
		dst[i] = ft_strdup(src[i]);
		if (!dst[i])
			return (ft_free((void **)dst[i], i), NULL);
	}
	dst[i] = NULL;
	return (dst);
}
t_cmd	*data_cpy(t_cmd *src)
{
	t_cmd	*dst;

	dst = data_init();
	dst->token = array_cpy(src->token);
	dst->cmd = ft_strdup(src->cmd);
	dst->cmd_path = ft_strdup(src->cmd_path);
	dst->cmd_args = array_cpy(src->cmd_args);
	dst->in_fd = src->in_fd;
	dst->out_fd = src->out_fd;
	dst->infile = ft_strdup(src->infile);
	dst->outfile = ft_strdup(src->outfile);
	dst->limiter = ft_strdup(src->limiter);
	dst->has_infile = src->has_infile;
	dst->has_outfile = dst->has_outfile;
	dst->tmp_pipe[0] = src->tmp_pipe[0];
	dst->tmp_pipe[1] = src->tmp_pipe[1];
	dst->pip[0][0] = src->pip[0][0];
	dst->pip[1][0] = src->pip[1][0];
	dst->pip[0][1] = src->pip[0][1];
	dst->pip[1][1] = src->pip[1][1];
	return (dst);
}
t_list	*mk_cmdlist(t_list **env_list, char *cmd_str, int *exit_status)
{
	char	**token;
	char	**part_token;
	t_cmd	*data;
	t_list	*cmd_list;
	int	end;
	int	i;

	i = 0;
	cmd_list = NULL;
	token = tokenize(cmd_str);
	while (token[i])
	{
		end = find_pipe(token, &i);
		part_token = get_cmd_token(token, i, end);
		i = end;
		data = data_parsing(env_list, part_token, exit_status);
		ft_lstadd_back(&cmd_list, ft_lstnew(data_cpy(data)));
	}
	return (cmd_list);
}

int is_builtin(char *cmd)
{
    return (
		!ft_strncmp(cmd, "echo", 5) ||
		!ft_strncmp(cmd, "cd",   3) ||
		!ft_strncmp(cmd, "exit", 5) ||
		!ft_strncmp(cmd, "pwd", 4) ||
		!ft_strncmp(cmd, "env", 4) ||
		!ft_strncmp(cmd, "unset", 6) ||
		!ft_strncmp(cmd, "export", 7)
    );
}
