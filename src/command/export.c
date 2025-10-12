/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:36:15 by miricci           #+#    #+#             */
/*   Updated: 2025/10/12 11:59:23 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export(t_list **env_list, char *str)
{
	char	*name;
	char	*value;
	int	name_len;
	t_list	*node;
	
	// ft_putendl_fd(str, 1);
	value = ft_strchr(str, '=');
	if (value)
	{
		value++;
		name = ft_substr(str, 0, ft_indchr(str, '='));
	}
	else
		name = str;
	name_len = ft_strlen(name);
	// ft_putendl_fd(name, 1);
	node = *env_list;
	while (node)
	{
		if (!ft_strncmp(name, (char *)node->content, name_len) && !ft_strncmp((char *)node->content + name_len, "=", 1))
		{
			if (value)
				ft_memcpy(node->content, str, ft_strlen(node->content));
			return ;
		}
		node = node->next;
	}
	if (value)
	{
		// ft_putendl_fd(str, 1);
		// ft_putendl_fd(name, 1);
		t_list *new_var = ft_lstnew(str);
		new_var->next = *env_list;
		// printf("%s\n", (char *)new_var->content);
		// printf("%p\n", new_var->next);
		*env_list = new_var;
	}
	node = *env_list;
	while (node)
	{
		printf("%s\n%p\n", (char *)node->content, node->next);
		node=node->next;
	}
}
