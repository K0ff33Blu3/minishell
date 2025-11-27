/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 18:02:20 by miricci           #+#    #+#             */
/*   Updated: 2025/11/27 18:03:42 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_error(t_env *env_node, char *str)
{
	ft_putstr_fd("export: \"", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd("\": not a valid identifier", STDERR_FILENO);
	free_env(env_node);
}

void	print_exp(t_list *node)
{
	t_env	*env;

	env = (t_env *)node->content;
	if (env->value)
		printf("declare -x %s=\"%s\"\n", env->name, env->value);
	else
		printf("declare -x %s\n", env->name);
}

int	check_name(char	*name)
{
	int	i;

	i = 0;
	if (!name || name[0] == '\0')
		return (0);
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (0);
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
