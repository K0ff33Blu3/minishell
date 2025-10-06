/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 12:26:24 by miricci           #+#    #+#             */
/*   Updated: 2025/10/06 18:50:20 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void 	printlst_node(t_list *node)
{
	printf("%s\n", (char *)node->content);
	printf("%p\n", node->next);
}

void	unset(t_list **env_list, char **var)
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
		while (node->next)
		{
			if (!ft_strncmp(var[i], (char *)node->next->content, len) && !ft_strncmp((char *)node->next->content + len, "=", 1))
			{
				printf("\nNODE->NEXT\n");
				printlst_node(node->next);
				tmp = node->next;
				printf("\nTMP\n");
				printlst_node(tmp);
				node->next = tmp->next;
				printf("\nNODE->NEXT\n");
				printlst_node(node->next);
				free(tmp);
				break ;
			}
			node = node->next;
		}
		i++;
	}
}