/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:50:27 by miricci           #+#    #+#             */
/*   Updated: 2025/11/27 18:53:34 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_last_sig = 0;

static void	process(char *cmd_line, int *exit_status, t_list **env_list)
{
	t_list	**cmd_list;
	pid_t	pid;
	int		status;

	cmd_list = mk_cmdlist(env_list, cmd_line, exit_status);
	if (!cmd_list)
	{
		if (g_last_sig == SIGINT)
		{
			*exit_status = 130;
			g_last_sig = 0;
		}
		return ;
	}
	if (ft_single_builtin(cmd_list, env_list, exit_status))
		return ;
	setup_father();
	open_pipeline(cmd_list);
	pid = creat_children(cmd_list, env_list, *exit_status);
	waitpid(pid, &status, 0);
	check_signals(status, exit_status);
	while (wait(NULL) != -1)
		;
	ft_lstclear(cmd_list, clean_data);
}

static void	read_command_loop(t_list **env_list, int *exit_status)
{
	char	*cmd_line;
	
	while (1)
	{
		cmd_line = readline(PROMPT);
		if (!cmd_line)
		{
			printf("exit\n");
			return ;
		}
		if (*cmd_line && !is_emptystr(cmd_line))
		{
			add_history(cmd_line);
			process(cmd_line, exit_status, env_list);
		}
		else
			free(cmd_line);
		if (g_last_sig != 0)
		{
			*exit_status = g_last_sig;
			g_last_sig = 0;
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	static t_list	**env_list;
	int				exit_status;

	(void)argc;
	(void)argv;
	waiting_signals();
	env_list = env_init(envp);
	exit_status = 0;
	read_command_loop(env_list, &exit_status);
	ft_lstclear(env_list, free_env);
	rl_clear_history();
	return (exit_status);
}
