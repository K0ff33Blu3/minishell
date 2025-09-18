/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 20:29:23 by miricci           #+#    #+#             */
/*   Updated: 2025/09/18 11:21:07 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_cmdline *data)
{
	char	*target;

	if (array_size((void **)data->cmd_args) > 2)
		return (write(2, "minishell: cd: too many arguments\n", 34), 1);
	if (!data->cmd_args[1])
		target = ft_strdup(getenv("HOME"));
	else
	target = ft_strdup(data->cmd_args[1]);
	if (chdir(target))
		return (perror("minishell: cd"), 1);
	return (0);
}