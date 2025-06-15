/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:41:20 by emondo            #+#    #+#             */
/*   Updated: 2025/06/15 11:56:37 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(char **envp)
{
	int	bytes;

	while (*envp)
		bytes = printf("%s\n", *envp++);
	if (bytes <= 0)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}

void	pwd(void)
{
	char	*current_path;
	int	bytes;
	
	current_path = getenv("PWD");
	bytes = printf("%s\n", current_path);
	if (bytes <= 0)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}

static int	check_flag(char **cmd_args)
{
	int	i;
	int	j;

	i = 1;
	while (cmd_args[i])
	{
		if (!ft_strncmp(cmd_args[i], "-n", 2))
		{
			j = 1;
			while(cmd_args[i][j])
			{
				if (cmd_args[i][j] != 'n')
					return (i);
				j++;
			}
			i++;
		}
		else
			return (i);
	}
	return (i);
}

void	echo(t_cmdline *data)
{
	int	i;
	int	flag;
	
	flag = check_flag(data->cmd_args);
	i = flag;
	while(data->cmd_args[i])
	{
		ft_putstr_fd(data->cmd_args[i], STDOUT_FILENO);
		if (data->cmd_args[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (flag == 1)
		ft_putstr_fd("\n", STDOUT_FILENO);
	exit(EXIT_SUCCESS);
}