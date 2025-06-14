/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:15:11 by miricci           #+#    #+#             */
/*   Updated: 2025/06/14 11:40:32 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_not_found(t_cmdline *data)
{
	ft_putstr_fd(data->cmd, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	ft_free((void **)data->cmd_args, -1);
	close(data->out_fd);
	close_pipe(data->pip);
	free(data->cmd_path);
	free(data->cmd);
	exit(CMD_NOT_FOUND);
}

static char	*make_path(char *str, char *cmd)
{
	char	*part_path;
	char	*path;

	part_path = ft_strjoin(str, "/");
	path = ft_strjoin(part_path, cmd);
	free(part_path);
	return (path);
}

char	*find_cmd_path(t_cmdline *data)
{
	char	**array;
	char	*path;
	int		i;
	char	*env_path;

	if (!access(data->cmd, X_OK))
		return (data->cmd);
	i = 0;
	env_path = getenv("PATH");
	if (!env_path)
		cmd_not_found(data);
	array = ft_split(env_path, ':');
	i = 0;
	while (array[i])
	{
		path = make_path(array[i], data->cmd);
		if (!access(path, X_OK))
			return (ft_free((void **)array, -1), path);
		free(path);
		i++;
	}
	i = 0;
	ft_free((void **)array, -1);
	return (NULL);
}