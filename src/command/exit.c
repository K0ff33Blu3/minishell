/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 20:30:11 by miricci           #+#    #+#             */
/*   Updated: 2025/10/24 19:22:38 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_cmd(t_cmd *data)
{
	int	code;

	code = 0;
	if (data && data->cmd_args && data->cmd_args[1])
		code = ft_atoi(data->cmd_args[1]);
	if (data)
		clean_data(data);
	return(exit(code), code);
}
