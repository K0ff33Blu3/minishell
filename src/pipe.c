/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 18:12:25 by miricci           #+#    #+#             */
/*   Updated: 2025/11/30 19:30:56 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipe(int pip[2])
{
	if (pip[0] > 2)
		close(pip[0]);
	if (pip[1] > 2)
		close(pip[1]);
}

void	handle_pipe(t_list **head, t_list *node)
{
	t_cmd	*data;
	t_cmd	*data_nxt;
	int		node_i;

	node_i = ft_lstindex(*head, node);
	data = (t_cmd *)node->content;
	if (node->next)
		data_nxt = (t_cmd *)((node->next)->content);
	else
		data_nxt = NULL;
	if (node_i < 0)
		return ;
	if (node_i > 0 && !data->has_infile)
		ft_dup2(data->pip[0], STDIN_FILENO);
	if (node->next && !data->has_outfile)
		ft_dup2(data_nxt->pip[1], STDOUT_FILENO);
	if (node_i > 0)
		close(data->pip[0]);
	if (node->next)
		close(data_nxt->pip[1]);
	close_pipeline(head, node);
}

pid_t	creat_child(t_list **head, t_list *node, t_list **env_list, int *st)
{
	pid_t	pid;
	t_cmd	*data;

	pid = fork();
	data = (t_cmd *)node->content;
	if (pid < 0)
		ft_error(env_list, head, "fork", EXIT_FAILURE);
	if (pid == 0)
	{
		reset_signals();
		handle_pipe(head, node);
		if (is_builtin(data->cmd) == 2)
		{
			exec_status_builtin(head, data, env_list, st);
			exit(*st);
		}
		redirect(head, env_list, data);
		if (is_builtin(data->cmd) == 1)
			exec_simple_builtin(head, data, env_list);
		exec_command(head, data, env_list);
	}
	else
		close_fd_parent(head, node);
	return (pid);
}

void	open_pipeline(t_list **head)
{
	t_list	*node;
	t_cmd	*data;

	node = *head;
	while (node)
	{
		if (node->next)
		{
			data = (t_cmd *)node->next->content;
			if (node && pipe(data->pip) == -1)
				return (perror("pipe"));
		}
		node = node->next;
	}
}

int	creat_children(t_list **cmd_list, t_list **env, int status)
{
	t_list	*node;
	pid_t	pid;

	node = *cmd_list;
	while (node)
	{
		pid = creat_child(cmd_list, node, env, &status);
		node = node->next;
	}
	return (pid);
}
