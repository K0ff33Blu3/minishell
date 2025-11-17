/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miricci <miricci@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:15:11 by miricci           #+#    #+#             */
/*   Updated: 2025/11/17 18:32:46 by miricci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	cmd_not_found(t_cmd *data)
// {
// 	ft_putstr_fd(data->cmd, STDERR_FILENO);
// 	ft_putstr_fd(": command not found\n", STDERR_FILENO);
// 	ft_free((void **)data->cmd_args, -1);
// 	close(data->out_fd);
// 	close_pipe(data->pip);
// 	free(data->cmd_path);
// 	free(data->cmd);
// 	// if (array_size((void **)data->all_cmd_lines) == 1)
// 	// 	return ;
// 	exit(CMD_NOT_FOUND);
// }

static char	*make_path(char *str, char *cmd)
{
	char	*part_path;
	char	*path;

	part_path = ft_strjoin(str, "/");
	path = ft_strjoin(part_path, cmd);
	free(part_path);
	return (path);
}

int	check_cmd_path(char *path)
{
	struct stat	st;

	if (!path)
		return (CMD_NOT_FOUND);
	if (ft_strchr(path, '/'))
	{
		if (!stat(path, &st))
		{
			if (!access(path, X_OK))
			{
				if (S_ISDIR(st.st_mode))
					return (IS_DIR);
				else
					return (0);
			}
			return (NO_PERM_X);
		}
		return (CMD_NOT_FOUND);
	}
	return (-1);
}

char	*find_cmd_path(t_list **env_list, t_cmd *data)
{
	char	**array;
	char	*path;
	int		i;
	char	*env_path;

	if (check_cmd_path(data->cmd) != -1)
		return (ft_strdup(data->cmd));
	i = 0;
	env_path = ft_getenv(env_list, "PATH");
	if (!env_path)
		return (NULL);
	array = ft_split(env_path, ':');
	i = 0;
	while (array[i])
	{
		path = make_path(array[i], data->cmd);
		if (check_cmd_path(path) != CMD_NOT_FOUND)
			return (ft_free((void **)array, -1), path);
		free(path);
		i++;
	}
	i = 0;
	ft_free((void **)array, -1);
	return (NULL);
}
