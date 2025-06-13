#include "minishell.h"

int	execute_builtin(t_cmdline *data)
{
	if (ft_strncmp(data->cmd, "echo", 5) == 0)
		echo_builtin(data);
	return (0);
}
