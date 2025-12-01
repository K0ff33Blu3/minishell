/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 17:13:45 by elmondo           #+#    #+#             */
/*   Updated: 2025/12/01 16:02:48 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc_sigint(int signum)
{
	if (signum == SIGINT)
	{
		g_last_sig = SIGINT;
		close(STDIN_FILENO);
		rl_done = 1;
	}
}

void	here_doc_signals(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = here_doc_sigint;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGTSTP, &sa, NULL);
}

void	reset_signals(void)
{
	struct sigaction	sa;

	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_DFL;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGTSTP, &sa, NULL);
}

void	ft_signum(int signum)
{
	g_last_sig = signum;
}

void	clean_sigint(t_cmd *cmd)
{
	g_last_sig = SIGINT;
	close_pipe(cmd->tmp_pipe);
	write(STDOUT_FILENO, "\n", 1);
}
