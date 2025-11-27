/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:50:27 by miricci           #+#    #+#             */
/*   Updated: 2025/11/26 15:14:23 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_last_sig = 0;

void	close_pipeline(t_list **cmd_list, t_list* cmd_node)
{
	t_list*	node;
	
	node = *cmd_list;	
	while (node)
	{
		if (node != cmd_node)
			close_pipe(((t_cmd *)(node->content))->pip);
		node = node->next;
	}
}

pid_t creat_children(t_list **head, t_list *node, t_list **env_list, int *exit_status)
{
	pid_t pid;
	int node_index;
	t_cmd *data;
	t_cmd *data_nxt;

	pid = fork();
	node_index = ft_lstindex(*head, node);
	data = (t_cmd *)node->content;
	if (node->next)
		data_nxt = (t_cmd *)((node->next)->content);
	else
		data_nxt = NULL;
	if (node_index < 0)
		return (-1);
	if (pid < 0)
		ft_error(env_list, head, "fork", EXIT_FAILURE);
	if (pid == 0)
	{
		reset_signals();
		if (node_index > 0 && !data->has_infile)
		{
			dup2(data->pip[0], STDIN_FILENO);
			close(data->pip[0]);
		}
		if (node->next && !data->has_outfile)
		{
			dup2(data_nxt->pip[1], STDOUT_FILENO);
			close(data_nxt->pip[1]);
		}
		close_pipeline(head, node);
		if (node_index > 0)
			close(data->pip[0]);
		if (node->next)
			close(data_nxt->pip[1]);
		if (exec_status_builtin(head, data, env_list, exit_status))
		{
			clean_data(data);
			exit(*exit_status);
		}
		redirect(head, env_list, data);
		if (is_builtin(data->cmd) == 1)
			exec_simple_builtin(head, data, env_list);
		exec_command(head, data, env_list);
	}
	else
	{
		if (node_index > 0)
			close(data->pip[0]);
		if (node_index < ft_lstsize(*head) - 1)
			close(data_nxt->pip[1]);
		if (data->has_infile && data->in_fd > 2)
			close(data->in_fd);
		if (data->has_outfile && data->out_fd > 2)
			close(data->out_fd);
	}
	return (pid);
}

void process(char *cmd_line, int *exit_status, t_list **env_list)
{
	t_list	**cmd_list;
	t_list	*node;
	pid_t	pid;
	int	status;

	cmd_list = mk_cmdlist(env_list, cmd_line, exit_status);
	if (!cmd_list)
		return ;
	if (ft_lstsize(*cmd_list) == 1 && exec_status_builtin(cmd_list, (t_cmd *)(*cmd_list)->content, env_list, exit_status))
		return (free(*cmd_list), free(cmd_list));
	else
	{
		setup_father();
		node = *cmd_list;
		while (node)
		{
			if (node && pipe(((t_cmd *)(node->content))->pip) == -1)
				ft_error(env_list, cmd_list, "pipe", EXIT_FAILURE);
			node = node->next;
		}
		node = *cmd_list;
		while (node)
		{
			pid = creat_children(cmd_list, node, env_list, exit_status);
			node = node->next;
		}
		node = *cmd_list;
		waitpid(pid, &status, 0);
		check_signals(status, exit_status);
	}
	while (wait(NULL) != -1)
		;
	ft_lstclear(cmd_list, clean_data);
}

int main(int argc, char **argv, char **envp)
{
	char	*cmd_line;
	int	exit_status;
	static t_list	**env_list;

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
			break;
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
