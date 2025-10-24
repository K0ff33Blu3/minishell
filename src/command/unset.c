/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 12:26:24 by miricci           #+#    #+#             */
/*   Updated: 2025/10/24 19:23:30 by miricci          ###   ########.fr       */
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

	i = 1;
	while (var[i])
	{
		len = ft_strlen(var[i]);
		node = *env_list;
		if (!ft_strncmp(var[i], (char *)node->content, len) && !ft_strncmp((char *)node->content + len, "=", 1))
		{
			*env_list = node->next;
			free(node);
			break ;
		}
		while (node->next)
		{
			if (!ft_strncmp(var[i], (char *)node->next->content, len) && !ft_strncmp((char *)node->next->content + len, "=", 1))
			{
				tmp = node->next;
				node->next = tmp->next;
				free(tmp);
				break ;
			}
			node = node->next;
		}
		i++;
	}
	return (0);
}
