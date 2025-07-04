/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 12:02:37 by miricci           #+#    #+#             */
/*   Updated: 2025/06/16 14:30:36 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	free_cmdline(t_cmdline *data)
{
	if (!data)
		return ;
	if (data->cmd)
		free(data->cmd);
	if (data->cmd_path)
		free(data->cmd_path);
	if (data->cmd_args)
		ft_free((void **)data->cmd_args, -1);
	if (data->all_cmd_lines)
		ft_free((void **)data->all_cmd_lines, -1);
	if (data->token)
		ft_free((void **)data->token, -1);
	free(data);
}
// void	clear_buffer()
// {
// 	rl_clear_history();
// 	free(cmd_line);
// }

void	close_pipe(int pip[2][2])
{
	close(pip[0][0]);
	close(pip[0][1]);
	close(pip[1][0]);
	close(pip[1][1]);
}