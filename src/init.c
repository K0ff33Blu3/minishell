/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 12:07:04 by miricci           #+#    #+#             */
/*   Updated: 2025/11/27 14:02:50 by miricci          ###   ########.fr       */
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
