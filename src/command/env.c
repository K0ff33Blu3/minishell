/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 20:27:52 by miricci           #+#    #+#             */
/*   Updated: 2025/09/18 11:13:34 by miricci          ###   ########.fr       */
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
