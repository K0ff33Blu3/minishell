/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:03:04 by miricci           #+#    #+#             */
/*   Updated: 2025/06/16 16:24:08 by miricci          ###   ########.fr       */
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

void	data_parsing(char *cmd_str, t_cmdline *data)
{
	data->token = get_data_token(cmd_str);
	data->has_infile = handle_input_redir(data);
	data->has_outfile = handle_output_redir(data);
	data->cmd_args = parse_cmd_args(data->token);

	if (!data->cmd_args || !data->cmd_args[0])
	{
		data->cmd = NULL;
		data->cmd_path = NULL;
		return ;
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
}
int is_builtin(char *cmd)
{
    return (
		ft_strncmp(cmd, "echo", 5) == 0 ||
		ft_strncmp(cmd, "cd",   3) == 0 ||   // ← aggiungi questa
		ft_strncmp(cmd, "exit", 5) == 0
    );
}
