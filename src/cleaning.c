/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 12:02:37 by miricci           #+#    #+#             */
/*   Updated: 2025/11/13 13:21:26 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_data(void *ptr)
{
	t_cmd	*data;

	data = (t_cmd *)ptr;
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
	if (data->in_fd > 2)
		close(data->in_fd);
	if (data->outfile)
		free(data->outfile);
	if (data->out_fd > 2)
		close(data->out_fd);
	if (data->limiter)
		free(data->limiter);
	close_pipe(data->pip);
	free(data);
}

void	free_env(void *ptr)
{
	t_env	*env;

	env = (t_env *)ptr;
	if (env)
	{
		if (env->name)
			free(env->name);
		if (env->value)
			free(env->value);
		free(env);
	}
}

void	close_pipe(int pip[2])
{
	close(pip[0]);
	close(pip[1]);
}

void	ft_error(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	error_msg()
{
	
}