/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emondo <emondo@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:41:20 by emondo            #+#    #+#             */
/*   Updated: 2025/05/27 17:41:59 by emondo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(char **envp)
{
	int	bytes;

	while (*envp)
		bytes = printf("%s\n", *envp++);
	return (bytes);
}

int	echo(char *str, int n)
{
	int	bytes;

	if (n == 0)
		bytes = printf("%s\n", str);
	else
		bytes = printf("%s", str);
	return (bytes);	
}

int	pwd(void)
{
	char	*current_path;
	int	bytes;
	
	current_path = getenv("PWD");
	bytes = printf("%s\n", current_path);
	if (bytes <= 0)
		exit (EXIT_FAILURE);
	return (bytes);
}