/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 12:26:24 by miricci           #+#    #+#             */
/*   Updated: 2025/10/27 07:33:54 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	printlst_node(t_list *node)
// {
// 	printf("%s\n", (char *)node->content);
// 	printf("%p\n", node->next);
// }

int	unset(t_list **env_list, char **var)
{
	int		len;
	int		i;
	t_list	*node;
	t_list	*tmp;
	t_env	*env;

	i = 1;
	while (var[i])
	{
		len = ft_strlen(var[i]);
		node = *env_list;
		if (!node)
			return (perror("env_list"), 1);
		env = (t_env *)node->content;
		if (!ft_strncmp(var[i], env->name, len + 1))
		{
			*env_list = node->next;
			ft_lstdelone(node, free_env);
		}
		while (node->next)
		{
			env = (t_env *)node->next->content;
			if (!ft_strncmp(var[i], env->name, len + 1))
			{
				tmp = node->next;
				node->next = tmp->next;
				ft_lstdelone(tmp, free_env);
				break ;
			}
			node = node->next;
		}
		i++;
	}
	return (0);
}
