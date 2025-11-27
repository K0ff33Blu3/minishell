/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:50:27 by miricci           #+#    #+#             */
/*   Updated: 2025/11/27 15:11:56 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_last_sig = 0;

void	close_pipeline(t_list **cmd_list, t_list *cmd_node)
{
	t_list	*node;

	node = *cmd_list;
	while (node)
	{
		if (node != cmd_node)
			close_pipe(((t_cmd *)(node->content))->pip);
		node = node->next;
	}
}

void	close_fd_parent(t_list **cmd, t_list *node)
{
	int		node_i;
	t_cmd	*data;
	t_cmd	*data_nxt;

	node_i = ft_lstindex(*cmd, node);
	data = (t_cmd *)node->content;
	if (node->next)
		data_nxt = (t_cmd *)((node->next)->content);
	else
		data_nxt = NULL;
	if (node_i < 0)
		return ;
	if (node_i > 0)
		close(data->pip[0]);
	if (node_i < ft_lstsize(*cmd) - 1)
		close(data_nxt->pip[1]);
	if (data->has_infile && data->in_fd > 2)
		close(data->in_fd);
	if (data->has_outfile && data->out_fd > 2)
		close(data->out_fd);
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
	data = (t_cmd *)node->content;
	while (node)
	{
		if (node && pipe(data->pip) == -1)
			return (perror("pipe"));
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
		pid = creat_child(cmd_list, node, env, status);
		node = node->next;
	}
}

void	process(char *cmd_line, int *exit_status, t_list **env_list)
{
	t_list	**cmd_list;
	t_list	*node;
	pid_t	pid;
	t_cmd	*data;
	int		status;

	cmd_list = mk_cmdlist(env_list, cmd_line, exit_status);
	if (!cmd_list)
		return ;
	node = *cmd_list;
	data = (t_cmd *)node->content;
	if (ft_lstsize(node) == 1 && is_builtin(data->cmd) == 2)
	{
		exec_status_builtin(cmd_list, data, env_list, exit_status);
		return (free(*cmd_list), free(cmd_list));
	}
	else
	{
		setup_father();
		open_pipeline(cmd_line);
		node = *cmd_list;
		pid = creat_children(cmd_list, env_list, status);
		waitpid(pid, &status, 0);
		check_signals(status, exit_status);
	}
	while (wait(NULL) != -1)
		;
	ft_lstclear(cmd_list, clean_data);
}

int	main(int argc, char **argv, char **envp)
{
	char	*cmd_line;
	static t_list	**env_list;
	int		exit_status;

	(void)argc;
	(void)argv;
	waiting_signals();
	env_list = env_init(envp);
	exit_status = 0;
	while (1)
	{
		cmd_line = readline(PROMPT);
		if (!cmd_line)
		{
			printf("exit\n");
			break ;
		}
		if (*cmd_line && !is_emptystr(cmd_line))
		{
			add_history(cmd_line);
			process(cmd_line, &exit_status, env_list);
		}
		else
			free(cmd_line);
		if (g_last_sig != 0)
		{
			exit_status = g_last_sig;
			g_last_sig = 0;
		}
	}
	ft_lstclear(env_list, free_env);
	rl_clear_history();
	return (g_last_sig);
}
