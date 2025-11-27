/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 11:16:05 by miricci           #+#    #+#             */
/*   Updated: 2025/11/27 14:02:43 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_emptystr(char *str)
{
	while (*str)
	{
		if (!ft_isspace(*str))
			return (0);
		str++;
	}
	return (1);
}

char	*ft_getenv(t_list **env_list, char *name)
{
	t_list	*node;
	t_env	*env;
	int		name_len;

	node = *env_list;
	name_len = ft_strlen(name);
	while (node)
	{
		env = (t_env *)node->content;
		if (!ft_strncmp(name, env->name, name_len))
			return (ft_strdup(env->value));
		node = node->next;
	}
	return (NULL);
}
