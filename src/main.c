/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:50:27 by miricci           #+#    #+#             */
/*   Updated: 2025/10/10 14:29:41 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_last_sig = 0;
int	g_exit_status = 0;

void	process(char *cmd_line, t_list **env_list)
{
	t_cmdline	*data;
	int	size;

	data = data_init();
	data->all_cmd_lines = str_split(cmd_line, '|');
	if (!data->all_cmd_lines)
		return ;
	size = array_size((void **)data->all_cmd_lines);
	if (size == 1)
		one_cmd(data, 1, env_list);
	else
		piping(data, size, env_list);
	while (wait(NULL) != -1)
		;
	free_cmdline(data);
	free(cmd_line);
}

int	main(int argc, char **argv, char **envp)
{
	char	*cmd_line;
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
			process(cmd_line, env_list);
		}
	}
	free(cmd_line);
	rl_clear_history();
	return (g_last_sig);
}
