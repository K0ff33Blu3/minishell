/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:36:15 by miricci           #+#    #+#             */
/*   Updated: 2025/10/12 14:43:34 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	change_or_create(t_list **env_list, char *name, char *value, char *str)
{
	t_list	*node;
	int	name_len;
	
	name_len = ft_strlen(name);
	node = *env_list;
	while (node)
	{
		if (!ft_strncmp(name, (char *)node->content, name_len) && !ft_strncmp((char *)node->content + name_len, "=", 1))
		{
			if (value)
			{
				free(node->content);	
				node->content = ft_strdup(str);
			}
			return ;
		}
		node = node->next;
	}
	if (value)
	{
		t_list *new_var = ft_lstnew(ft_strdup(str));
		new_var->next = *env_list;
		*env_list = new_var;
	}
}

static void	export_one(t_list **env_list, char *str)
{
	char	*value;
	char	*name;
	
	value = ft_strchr(str, '=');
	if (value)
	{
		value++;
		name = ft_substr(str, 0, ft_indchr(str, '='));
	}
	else
		name = str;
	change_or_create(env_list, name, value, str);
}

void	export(t_list **env_list, char **str)
{
	int	i;

	i = 0;
	while (str[++i])
	{
		printf("%s\n", str[i]);
		export_one(env_list, str[i]);
	}
}
