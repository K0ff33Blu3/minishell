/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:50:27 by miricci           #+#    #+#             */
/*   Updated: 2025/05/16 12:54:37 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*cmd_line;
	
	(void)argc;
	(void)argv;
	(void)envp;
	while (1)
	{
		cmd_line = readline(PROMPT);
		if (!cmd_line)
			break ;
		if (*cmd_line)
			add_history(cmd_line);
		if (!ft_strncmp(cmd_line, "env", 2))
			env(envp);
		else if (!ft_strncmp(cmd_line, "pwd", 2))
			pwd();
	}
	rl_clear_history();
	free(cmd_line);
	return (0);
}