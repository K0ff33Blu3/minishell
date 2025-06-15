#include "minishell.h"

void	handle_sigint_prompt(int signum)
{
	if (signum == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	g_last_sig = signum;	
}

void	setup_shell_signals(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	sa.sa_flags   = SA_RESTART;
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGTSTP, &sa, NULL);
	sa.sa_handler = handle_sigint_prompt;
	sa.sa_flags   = SA_RESTART;
	sigaction(SIGINT,  &sa, NULL);
}
void	reset_signals_default(void)
{
	struct sigaction sa;

	/* handler di default */
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_DFL;

	/* applica a SIGINT, SIGQUIT e SIGTSTP */
	sigaction(SIGINT,  &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGTSTP, &sa, NULL);
}

