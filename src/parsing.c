/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:03:04 by miricci           #+#    #+#             */
/*   Updated: 2025/11/27 17:37:51 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
