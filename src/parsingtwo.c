/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingtwo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elmondo <elmondo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 17:33:16 by elmondo           #+#    #+#             */
/*   Updated: 2025/11/27 17:33:18 by elmondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
