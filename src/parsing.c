/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elmondo <elmondo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:03:04 by miricci           #+#    #+#             */
/*   Updated: 2025/11/27 17:00:21 by elmondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*rm_quotes(char *str)
{
	int		i;
	int		j;
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
			quote = str[i++];
			while (str[i] && str[i] != quote)
				no_quote[j++] = str[i++];
			if (str[i] == quote)
				i++;
		}
		else
			no_quote[j++] = str[i++];
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

static int	count_redir(char **token)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (token[i])
	{
		if (!is_redir(token, i))
			count++;
		i++;
	}
	return (count);
}

char	**parse_cmd_args(char **token, int *exit_status)
{
	int		i;
	int		j;
	int		arg_size;
	char	**arg;

	arg_size = array_size((void **)token) - (count_redir(token) * 2);
	arg = malloc(sizeof(char *) * (arg_size + 1));
	i = 0;
	j = 0;
	while (token[i])
	{
		if (!is_redir(token, i))
			i += 2;
		else if (is_redir(token, i) == SYNT_ERR)
		{
			*exit_status = SYNT_ERR;
			ft_perror(token[i + 1], *exit_status);
			return (ft_free((void **)arg, j), NULL);
		}
		else
			arg[j++] = ft_strdup(token[i++]);
	}
	arg[j] = NULL;
	return (arg);
}

char	**get_cmd_token(char **all_token, int start, int end)
{
	char	**result;
	int		i;

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
	data->cmd_args = parse_cmd_args(data->token, exit_status);
	if (!data->cmd_args || !data->cmd_args[0])
	{
		data->cmd = NULL;
		data->cmd_path = NULL;
		if (*exit_status == 2)
			return (ft_free((void **)part_token, -1), NULL);
	}
	data->has_infile = handle_input_redir(data);
	if (g_last_sig == SIGINT)
		return (NULL);
	data->has_outfile = handle_output_redir(data);
	data->cmd = ft_strdup(data->cmd_args[0]);
	if (is_builtin(data->cmd))
		data->cmd_path = NULL;
	else
		data->cmd_path = find_cmd_path(env_list, data);
	return (data);
}

t_list	**mk_cmdlist(t_list **env_list, char *cmd_str, int *status)
{
	char	**token;
	t_cmd	*data;
	t_list	**cmd_list;
	int		end;
	int		i;

	i = 0;
	token = tokenize(cmd_str);
	cmd_list = (t_list **)malloc(sizeof(t_list *));
	if (!cmd_list)
		return (NULL);
	*cmd_list = NULL;
	while (token[i])
	{
		end = find_pipe(token, &i);
		data = data_parsing(env_list, get_cmd_token(token, i, end), status);
		if (g_last_sig == SIGINT || !data)
			return (ft_free((void **)token, -1),
				ft_lstclear(cmd_list, clean_data), NULL);
		ft_lstadd_back(cmd_list, ft_lstnew(data));
		i = end;
	}
	ft_free((void **)token, -1);
	return (cmd_list);
}
