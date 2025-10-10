/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:36:15 by miricci           #+#    #+#             */
/*   Updated: 2025/10/10 16:06:37 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export(char *string, t_list **env_list)
{
	char	*name;
	char	*value;
	int	name_len;
	t_list	*node;
	
	value = ft_strchr(string, '=');
	if (value)
	{
		value++;
		name = ft_substr(string, 0, ft_indchr(string, '='));
	}
	else
		name = string;
	printf("%s\n", name);
	name_len = ft_strlen(name);
	node = *env_list;
	while (node)
	{
		if (!ft_strncmp(name, (char *)node->content, name_len) && !ft_strncmp((char *)node->content + name_len, "=", 1))
			return ;
		node = node->next;
	}
	if (value)
		ft_lstadd_back(env_list, ft_lstnew(string));
}
