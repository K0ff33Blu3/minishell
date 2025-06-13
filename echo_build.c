#include "minishell.h"

static int	check_flag(char **cmd_args)
{
	int	i;

	if (!ft_strncmp(cmd_args[1], "-n", 2))
	{
		i = 1;
		while(cmd_args[1][i])
		{
			if (cmd_args[1][i] != 'n')
				return (0);
			i++;
		}
		return (i);
	}
	else
		return (0);
}

int	echo_builtin(t_cmdline *data)
{
	int	i;
	int	flag;
	
	flag = check_flag(data->cmd_args);
	if (flag)
		i = 2;
	else
		i = 1;
	while(data->cmd_args[i])
	{
		ft_putstr_fd(data->cmd_args[i], 1);
		if (data->cmd_args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!flag)
		ft_putstr_fd("\n", 1);
	return (0);
}

