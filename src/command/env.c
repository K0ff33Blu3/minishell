/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 20:27:52 by miricci           #+#    #+#             */
/*   Updated: 2025/10/24 16:32:25 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(t_list **env_list)
{
	t_list		*node;
	t_env	*env;
	
	node = *env_list;
	while (node)
	{
		env = (t_env *)node->content;
		if (env->value)
			printf("%s=%s\n", env->name, env->value);
		node = node->next;
	}
	exit(EXIT_SUCCESS);
}
