/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 12:02:37 by miricci           #+#    #+#             */
/*   Updated: 2025/11/27 17:12:09 by miricci          ###   ########.fr       */
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
	if (pip[0] > 2)
		close(pip[0]);
	if (pip[1] > 2)
		close(pip[1]);
}

void	ft_redir_err(t_list **env, t_list **cmd, char *str, int code)
{
	ft_perror(str, code);
	ft_lstclear(env, free_env);
	ft_lstclear(cmd, clean_data);
	exit(EXIT_FAILURE);
}

void	ft_error(t_list **env_lst, t_list **cmd_lst, char *str, int exit_code)
{
	ft_perror(str, exit_code);
	if (exit_code == IS_DIR)
		exit_code++;
	ft_lstclear(env_lst, free_env);
	ft_lstclear(cmd_lst, clean_data);
	exit(exit_code);
}

void	ft_perror(char *str, int exit_code)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (exit_code == NOT_FOUND)
	{
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
	}
	else if (exit_code == IS_DIR)
	{
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd(": is a directory", STDERR_FILENO);
	}
	else if (exit_code == NO_PERM)
	{
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd(": permission denied", STDERR_FILENO);
	}
	else if (exit_code == SYNT_ERR)
	{
		ft_putstr_fd("syntax error near unexpected token \"", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd("\"", STDERR_FILENO);
	}
	else
		perror(str);
}
