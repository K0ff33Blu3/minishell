/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:50:27 by miricci           #+#    #+#             */
/*   Updated: 2025/10/21 17:57:19 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_last_sig = 0;

pid_t	creat_children(t_cmd *data, )
{
	
}

void	process(char *cmd_line, int *exit_status, t_list **env_list)
{
	t_list	*cmd_list;
	t_list	*node;
	pid_t	pid;
	// int	i;

	cmd_list = mk_cmdlist(env_list, cmd_line, exit_status);
	if (ft_lstsize(cmd_list) == 1 && exec_status_changing_builtin((t_cmd *)cmd_list->content, env_list))
		return ;
	else
	{
		node = cmd_list;
		while (node)
			creat_children();
	}
		
	// i = 0;
	// while (node)
	// {
	// 	printf("\n-----------%d------------\n", i);
	// 	print_cmd_struct(*(t_cmd *)(node->content), 1);
	// 	printf("\n-----------%d------------\n", i);
	// 	node = node->next;
	// 	i++;
	// }
	
	
	
}

// void	process(char *cmd_line, int *exit_status, t_list **env_list)
// {
// 	t_cmd	*data;
// 	int	size;

// 	data = data_init();
// 	data->all_cmd_lines = str_split(cmd_line, '|');
// 	if (!data->all_cmd_lines)
// 		return ;
// 	size = array_size((void **)data->all_cmd_lines);
// 	if (size == 1)
// 		*exit_status = one_cmd(data, exit_status, env_list);
// 	else
// 		*exit_status = piping(data, exit_status, size, env_list);
// 	while (wait(NULL) != -1)
// 		;
// 	clean_data(data);
// 	free(cmd_line);
// }

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
	}
	free(cmd_line);
	rl_clear_history();
	return (g_last_sig);
}
