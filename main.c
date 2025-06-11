/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:50:27 by miricci           #+#    #+#             */
/*   Updated: 2025/06/11 15:59:36 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_last_sig = 0;

int	main(int argc, char **argv, char **envp)
{
	char	*cmd_line;

	(void)argc;
	(void)argv;
	(void)envp;
	while (1)
	{
		ft_empty_initializer();
		cmd_line = readline(PROMPT);
		if (!cmd_line)
			break ;
		if (*cmd_line && !is_emptystr(cmd_line))
		{
			add_history(cmd_line);
			pipe_parsing(cmd_line);
		}
	}
	rl_clear_history();
	free(cmd_line);
	return (0);
}