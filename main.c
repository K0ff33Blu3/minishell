/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emondo <emondo@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:50:27 by miricci           #+#    #+#             */
/*   Updated: 2025/06/15 21:35:31 by emondo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_last_sig = 0;

void process(char *cmd_line, char **envp)
{
    t_cmdline *data = data_init();
    data->all_cmd_lines = str_split(cmd_line, '|');
    if (!data->all_cmd_lines)
        return ;
    int size = array_size((void **)data->all_cmd_lines);
    if (size == 1)
    {
        data_parsing(data->all_cmd_lines[0], data);
        if (data->cmd && ft_strncmp(data->cmd, "cd", 3) == 0)
        {
            execute_builtin(data);
            free_cmdline(data);
            free(cmd_line);
            return;
        }
    }
    if (size == 1)
        one_cmd(data, 1, envp);
    else
        piping(data, size, envp);

    while (wait(NULL) != -1)
        ;
    free_cmdline(data);
    free(cmd_line);
}

int	main(int argc, char **argv, char **envp)
{
	char	*cmd_line;

	(void)argc;
	(void)argv;
	while (1)
	{
		setup_shell_signals();
		cmd_line = readline(PROMPT);
		if (!cmd_line)
			break ;
		if (*cmd_line && !is_emptystr(cmd_line))
		{
			add_history(cmd_line);
			if (ft_strncmp(cmd_line, "exit", 4) == 0 && (cmd_line[4] == '\0' || cmd_line[4] == ' '))
			{
				t_cmdline	*data = data_init();  // solo per passare a exit_cmd
				data->cmd_args = str_split(cmd_line, ' ');
				exit_cmd(data);
			}
			process(cmd_line, envp);
		}
	}
	free(cmd_line);
	rl_clear_history();
	// clear_buffer();
	return (0);
}
