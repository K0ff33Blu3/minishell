/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emondo <emondo@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 11:11:36 by miricci           #+#    #+#             */
/*   Updated: 2025/11/09 15:51:09 by emondo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint_prompt(int signum)
{
	if (signum == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_last_sig = 128 + signum;
	}
}

void	setup_shell_signals(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	sa.sa_flags   = 0;
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGTSTP, &sa, NULL);
	sa.sa_handler = handle_sigint_prompt;
	sa.sa_flags   = 0;
	sigaction(SIGINT,  &sa, NULL);
}
void	setup_shell_signals_father(void)
{
	struct sigaction ign;

	ft_bzero(&ign, sizeof(ign));
	ign.sa_handler = SIG_IGN;
	sigaction(SIGINT,  &ign, NULL);
	sigaction(SIGQUIT, &ign, NULL);
}

void	apply_status_and_restore_prompt(int status, int *exit_status)
{
	int	sig;

	if (exit_status == NULL)
		return ;
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
		{
			write(STDOUT_FILENO, "\n", 1);
			*exit_status = 130;
		}
		else if (sig == SIGQUIT)
		{
			write(STDERR_FILENO, "Quit (core dumped)\n", 19);
			*exit_status = 131;
		}
		else
			*exit_status = 128 + sig;
	}
	else if (WIFEXITED(status))
		*exit_status = WEXITSTATUS(status);
	setup_shell_signals();
}
void	apply_status_and_restore_prompt_due(int status, int *exit_status)
{
	int	sig;

	if (exit_status == NULL)
		return ;
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
		{
			write(STDOUT_FILENO, "\n", 1);
			*exit_status = 130;
		}
		else if (sig == SIGQUIT)
		{
			write(STDERR_FILENO, "Quit (core dumped)\n", 19);
			*exit_status = 131;
		}
		else
			*exit_status = 128 + sig;
	}
	else if (WIFEXITED(status))
		*exit_status = WEXITSTATUS(status);
}

void	reset_signals_default(void)
{
	struct sigaction sa;

	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_DFL;
	sigaction(SIGINT,  &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGTSTP, &sa, NULL);
}

