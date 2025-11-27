/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 12:07:04 by miricci           #+#    #+#             */
/*   Updated: 2025/11/27 18:01:12 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*data_init(void)
{
	t_cmd	*data;

	data = (t_cmd *)malloc(sizeof(t_cmd));
	ft_memset(data, 0, sizeof(*data));
	if (!data)
		return (NULL);
	return (data);
}

t_list	**env_init(char **envp)
{
	t_list	**env_list;
	t_list	*node;

	env_list = (t_list **) malloc (sizeof(t_list *));
	if (!env_list)
		return (NULL);
	*env_list = ft_lstnew(mk_env(find_env_name(*envp), find_env_value(*envp)));
	envp++;
	while (*envp)
	{
		node = ft_lstnew(mk_env(find_env_name(*envp), find_env_value(*envp)));
		ft_lstadd_back(env_list, node);
		envp++;
	}
	return (env_list);
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
