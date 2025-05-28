#include "minishell.h"

void	ft_empty_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		re_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signum == SIGTSTP)
	{
		write(STDERR_FILENO, "\b\b  \b\b", 6);
	}
	else if (signum == SIGQUIT)
	{
		write(STDERR_FILENO, "\b\b  \b\b", 6);
	}
	g_last_sig = signum;	
}

void	ft_empty_initializer(void)
{
	struct sigaction	waiter;

	ft_bzero
	
	
}