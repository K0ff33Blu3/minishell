/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emondo <emondo@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:50:27 by miricci           #+#    #+#             */
/*   Updated: 2025/05/28 11:01:18 by emondo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_last_sig = 0;

int	main(int argc, char **argv, char **envp)
{
	char	*cmd_line;
	t_list **prova;
	
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
		prova = pipe_parsing(cmd_line);
		print_list(prova, "LIST");
		if (!ft_strncmp(cmd_line, "env", 2))
			env(envp);
		else if (!ft_strncmp(cmd_line, "pwd", 2))
			pwd();
		
	}
	rl_clear_history();
	free(cmd_line);
	return (0);
}