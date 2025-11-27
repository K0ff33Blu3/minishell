/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 12:26:24 by miricci           #+#    #+#             */
/*   Updated: 2025/11/26 15:11:15 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unset_one(t_list **env_list, char *var)
{
	int		len;
	t_env	*env;
	t_list	*node;
	t_list	*tmp;

	len = ft_strlen(var);
	node = *env_list;
	env = (t_env *)node->content;
	if (!ft_strncmp(var, env->name, len + 1))
	{
		*env_list = node->next;
		ft_lstdelone(node, free_env);
	}
	while (node->next)
	{
		env = (t_env *)node->next->content;
		if (!ft_strncmp(var, env->name, len + 1))
		{
			tmp = node->next;
			node->next = tmp->next;
			ft_lstdelone(tmp, free_env);
			break ;
		}
		node = node->next;
	}
}

int	unset(t_list **env_list, char **var)
{
	int		i;

	i = 0;
	while (var[++i])
		unset_one(env_list, var[i]);
	return (0);
}
