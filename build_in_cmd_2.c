/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in_cmd_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emondo <emondo@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 12:07:54 by miricci           #+#    #+#             */
/*   Updated: 2025/06/15 20:24:01 by emondo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_cmd(t_cmdline *data)
{
	if (data)
	{
		if (data->out_fd)
			close(data->out_fd);
		if (data->in_fd)
			close(data->in_fd);
		free_cmdline(data);
	}
	exit(EXIT_SUCCESS);
}


