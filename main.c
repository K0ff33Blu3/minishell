/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:50:27 by miricci           #+#    #+#             */
/*   Updated: 2025/05/30 12:27:24 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_last_sig = 0;

int	main(int argc, char **argv, char **envp)
{
	char	*cmd_line;
	// t_list **prova;
	
	(void)argc;
	(void)argv;
	(void)envp;
	while (1)
	{
		ft_empty_initializer();
		cmd_line = readline(PROMPT);
		if (!cmd_line)
			break ;
		if (*cmd_line)
			add_history(cmd_line);
		pipe_parsing(cmd_line);
		// print_list(prova, "LIST");
		// if (!ft_strncmp(cmd_line, "env", 2))
		// 	env(envp);
		// else if (!ft_strncmp(cmd_line, "pwd", 2))
		// 	pwd();
		rl_on_new_line();
		rl_redisplay();
	}
	rl_clear_history();
	free(cmd_line);
	return (0);
}