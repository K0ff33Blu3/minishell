/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 12:02:37 by miricci           #+#    #+#             */
/*   Updated: 2025/10/24 13:08:59 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_data(t_cmd *data)
{
	if (!data)
		return ;
	if (data->token)
		ft_free((void **)data->token, -1);
	if (data->cmd)
		free(data->cmd);
	if (data->cmd_path)
		free(data->cmd_path);
	if (data->cmd_args)
		ft_free((void **)data->cmd_args, -1);
	if (data->infile)
		free(data->infile);
	if (data->outfile)
		free(data->outfile);
	if (data->limiter)
		free(data->limiter);
	free(data);
}
// void	clear_buffer()
// {
// 	rl_clear_history();
// 	free(cmd_line);
// }

void	close_pipe(int pip[2])
{
	close(pip[0]);
	close(pip[1]);
	// close(pip[1][0]);
	// close(pip[1][1]);
}