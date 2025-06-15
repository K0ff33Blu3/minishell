/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in_cmd_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emondo <emondo@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 12:07:54 by miricci           #+#    #+#             */
/*   Updated: 2025/06/15 20:39:11 by emondo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_cmd(t_cmdline *data)
{
	int	code = 0;

	if (data && data->cmd_args && data->cmd_args[1])
		code = ft_atoi(data->cmd_args[1]);

	if (data)
		free_cmdline(data); // deve gestire campi nulli in sicurezza

	exit(code);
}


