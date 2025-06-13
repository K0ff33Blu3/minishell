/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 11:50:27 by miricci           #+#    #+#             */
/*   Updated: 2025/06/12 16:17:30 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_last_sig = 0;

void	process(char *cmd_line, char **envp)
{
	char	**split_cmd_line;
	int	size;
	int fd = open("output_check", O_RDWR);
	if (fd < 0)
		return ;
	split_cmd_line = ft_split(cmd_line, '|');
	if (!split_cmd_line)
		return ;
	size = array_size((void **)split_cmd_line);
	if (size == 1)
		one_cmd(split_cmd_line[0], 1, envp);
	else if (size > 1)
		piping(split_cmd_line, size, envp);
	while (wait(NULL) != -1)
		;
	ft_free((void **)split_cmd_line, -1);
}

int	main(int argc, char **argv, char **envp)
{
	char	*cmd_line;

	(void)argc;
	(void)argv;
	while (1)
	{
		ft_empty_initializer();
		cmd_line = readline(PROMPT);
		if (!cmd_line)
			break ;
		if (*cmd_line && !is_emptystr(cmd_line))
		{
			add_history(cmd_line);
			process(cmd_line, envp);
		}
	}
	rl_clear_history();
	free(cmd_line);
	return (0);
}