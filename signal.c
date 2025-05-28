#include "minishell.h"

void	ft_empty_handler(int signum)
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

void	ft_empty_initializer(void)
{
	struct sigaction	waiter;

	ft_bzero(&waiter, sizeof(waiter));
	waiter.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &waiter, NULL);
	sigaction(SIGTSTP, &waiter, NULL);
	waiter.sa_handler = ft_empty_handler;
	waiter.sa_flags = 0;
	sigaction(SIGINT, &waiter, NULL);
}
