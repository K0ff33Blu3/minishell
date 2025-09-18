/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 20:30:11 by miricci           #+#    #+#             */
/*   Updated: 2025/09/18 11:21:19 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_cmd(t_cmdline *data)
{
	int	code;

	code = 0;
	if (data && data->cmd_args && data->cmd_args[1])
		code = ft_atoi(data->cmd_args[1]);
	if (data)
		free_cmdline(data);
	exit(code);
}
