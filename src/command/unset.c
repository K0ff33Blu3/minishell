/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 12:26:24 by miricci           #+#    #+#             */
/*   Updated: 2025/10/07 19:40:10 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	printlst_node(t_list *node)
// {
// 	printf("%s\n", (char *)node->content);
// 	printf("%p\n", node->next);
// }

static void	remove_node(t_list **head, char *value)
{
	t_list	*node;
	t_list	*tmp;
	int		len;

	len = ft_strlen(value);
	node = *head;
	tmp = NULL;
	if (node && !ft_strncmp(node->content, value, len) && ((char *)node->content)[len] == '=')
	{
		*head = node->next;
		free(node);
		return ;
	}
	printf("SEGFAULT??");
	while (node && !ft_strncmp(node->content, value, len) && ((char *)node->content)[len] == '=')
	{
		printf("???SEGFAULT");
		tmp = node;
		node = node->next;
	}
	if (!node)
		return ;
	tmp->next = node->next;
	free(node);
	return ;
}

void	unset(t_list **env_list, char **var)
{
	int		i;

	i = 0;
	// print_list(env_list, "env_list");
	while (var[++i])
	{
		printf("SEGFAULT??");
		remove_node(env_list, var[i]);
	}
	print_list(env_list, "env_list");
}