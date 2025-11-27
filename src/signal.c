/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 11:11:36 by miricci           #+#    #+#             */
/*   Updated: 2025/11/27 18:00:16 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	simple_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_last_sig = 128 + signum;
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	waiting_signals(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGTSTP, &sa, NULL);
	sa.sa_handler = simple_handler;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}

void	setup_father(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = ft_signum;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	check_signals(int status, int *exit_status)
{
	if (exit_status == NULL)
		return ;
	if (g_last_sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		*exit_status = 130;
		g_last_sig = 0;
	}
	else if (g_last_sig == SIGQUIT)
	{
		write(STDERR_FILENO, "Quit (core dumped)\n", 19);
		*exit_status = 131;
		g_last_sig = 0;
	}
	else
		*exit_status = status >> 8;
	waiting_signals();
}
