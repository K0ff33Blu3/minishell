/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 20:30:11 by miricci           #+#    #+#             */
/*   Updated: 2025/11/26 13:01:44 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_cmd(t_list **env_list, t_list **cmd_list, t_cmd *data)
{
	int	code;

	code = 0;
	if (data && data->cmd_args && data->cmd_args[1])
		code = ft_atoi(data->cmd_args[1]);
	ft_lstclear(env_list, free_env);
	ft_lstclear(cmd_list, clean_data);
	return (exit(code), code);
}
