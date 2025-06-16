/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in_cmd_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 12:07:54 by miricci           #+#    #+#             */
/*   Updated: 2025/06/16 11:26:00 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_cmd(t_cmdline *data)
{
	int	code;
	
	code = 0;
	if (data && data->cmd_args && data->cmd_args[1])
		code = ft_atoi(data->cmd_args[1]);

	if (data)
		free_cmdline(data);
	exit(code);
}

int	ft_cd(t_cmdline *data)
{
	char	*oldpwd;
	char	*pwd;
	char	*target;

	if (data->cmd_args[1] && data->cmd_args[2])
		return (write(2, "minishell: cd: too many arguments\n", 34), 1);
	oldpwd = getcwd(NULL, 0);
	if (!data->cmd_args[1])
		target = getenv("HOME");
	else if (!ft_strncmp(data->cmd_args[1], "-", 2))
	{
		target = getenv("OLDPWD");
		if (!target)
			return (write(2, "minishell: cd: OLDPWD not set\n", 31), free(oldpwd), 1);
		write(1, target, ft_strlen(target));
		write(1, "\n", 1);
	}
	else
		target = data->cmd_args[1];
	if (chdir(target) != 0)
		return (perror("minishell: cd"), free(oldpwd), 1);
	pwd = getcwd(NULL, 0);
	setenv("OLDPWD", oldpwd, 1);
	setenv("PWD", pwd, 1);
	return (free(oldpwd), free(pwd), 0);
}




