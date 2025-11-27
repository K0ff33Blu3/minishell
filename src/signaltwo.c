#include "minishell.h"

void	check_signals_two(int status, int *exit_status)
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
