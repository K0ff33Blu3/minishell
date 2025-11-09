/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emondo <emondo@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:50:27 by miricci           #+#    #+#             */
/*   Updated: 2025/11/09 15:51:09 by emondo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_last_sig = 0;

pid_t	creat_children(t_list **head, t_list *node, t_list **env_list, int *exit_status)
{
	pid_t	pid;
	int	node_index;
	t_cmd	*data;
	t_cmd	*data_nxt;

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
		ft_error("fork");
	if (pid == 0)
	{
		reset_signals_default();
		if (node_index > 0 && !data->has_infile)
			dup2(data->pip[0], STDIN_FILENO);
		if (node->next && !data->has_outfile)
			dup2(data_nxt->pip[1], STDOUT_FILENO);
		if (node_index > 0)
			close(data->pip[0]);
		if (node->next)
			close(data_nxt->pip[1]);
		if (exec_status_changing_builtin(data, env_list, exit_status))
		{
			clean_data(data);
			exit(*exit_status);
		}
		redirect(data);
		exec_simple_builtin(data, env_list);
		exec_command(data, env_list);
	}
	else
	{
		if (node_index > 0)
			close(data->pip[0]);
		if (node_index < ft_lstsize(*head) - 1)
			close(data_nxt->pip[1]);
	}
	return (pid);		
}

void	process(char *cmd_line, int *exit_status, t_list **env_list)
{
	t_list	*cmd_list;
	t_list	*node;
	pid_t	pid;
	int	status;

	cmd_list = mk_cmdlist(env_list, cmd_line, exit_status);
	if (ft_lstsize(cmd_list) == 1 && exec_status_changing_builtin((t_cmd *)cmd_list->content, env_list, exit_status))
		return ;
	else
	{
		node = cmd_list;
		while (node)
		{
			if (node && pipe(((t_cmd *)(node->content))->pip) == -1)
				ft_error("pipe");
			node = node ->next;
		}
		node = cmd_list;
		while (node)
		{
			pid = creat_children(&cmd_list, node, env_list, exit_status);
			node = node->next;
		}
		waitpid(pid, &status, 0);
		apply_status_and_restore_prompt(status, exit_status);
	}
	while (wait(NULL) != -1)
		;
	
}

int	main(int argc, char **argv, char **envp)
{
	char	*cmd_line;
	int	exit_status;
	static t_list		**env_list;

	(void)argc;
	(void)argv;
	setup_shell_signals();
	env_list = env_init(envp);
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
		if (g_last_sig != 0)
		{
			exit_status = g_last_sig;
			g_last_sig = 0;
		}
	}
	free(cmd_line);
	ft_lstclear(env_list, free_env);
	rl_clear_history();
	return (g_last_sig);
}
